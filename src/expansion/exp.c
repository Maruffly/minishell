/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:22:15 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/07 18:02:26 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_expansion(t_ast *node, t_shell *sh)
{
	char	**args;
	t_token	*expanded_args;

	if (!node || !sh || !node->u_data.command.args)
		return ;
	expanded_args = NULL;
	args = node->u_data.command.args;
	while (*args)
	{
		if (*args)
			arg_expansion(*args, &expanded_args, sh);
		args++;
	}
	node->u_data.command.args = list_to_array(&expanded_args, sh);
	/* if (args)
		ft_free_split(args); */
	if (!node->u_data.command.args)
		error("expansion", "failed to convert tokens to array",
			EXIT_FAILURE, sh);
}

void	redirection_expansion(t_ast *node, t_shell *sh)
{
	char	*str;
	t_token	*expanded_args;

	if (!node || !sh || node->u_data.redirection.direction == HEREDOC)
		return ;
	expanded_args = NULL;
	str = node->u_data.redirection.file;
	arg_expansion(str, &expanded_args, sh);
	if (ft_lstsize_token(expanded_args) != 1
		|| !ft_strcmp(expanded_args->value, ""))
		error("wrong redirection", NULL, 1, sh);
	else
		node->u_data.redirection.file = expanded_args->value;
}

t_ast	*node_expansion(t_ast *node, t_shell *sh)
{
	if (!node || !sh)
		return (NULL);
	if (node->type == AST_COMMAND)
		command_expansion(node, sh);
	else if (node->type == AST_REDIRECTION)
		redirection_expansion(node, sh);
	return (node);
}
