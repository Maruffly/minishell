/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:22:15 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:43 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exp_wildcard_or_arg(char *arg, t_token **expanded_args,
								t_shell *sh)
{
	char	**exp_dirs;

	if (ft_strcmp(arg, "*/") == 0)
	{
		exp_dirs = expand_wildcard_dirs();
		if (exp_dirs)
			*expanded_args = append_tokens_to_list(*expanded_args, exp_dirs);
		ft_free_split(exp_dirs);
	}
	else
		arg_expansion(arg, expanded_args, sh);
	free(arg);
}

void	command_expansion(t_ast *node, t_shell *sh)
{
	char	**args;
	int		i;
	t_token	*expanded_args;

	if (!node || !sh || !node->u_data.command.args)
		return ;
	expanded_args = NULL;
	args = node->u_data.command.args;
	i = 0;
	while (args[i])
	{
		exp_wildcard_or_arg(args[i], &expanded_args, sh);
		i++;
	}
	free(args);
	node->u_data.command.args = list_to_array(&expanded_args, sh);
	if (expanded_args)
		free_token_list(expanded_args);
}

void	redirection_expansion(t_ast *node, t_shell *sh)
{
	char	*str;
	t_token	*expanded_args;
	char	*tmp;

	if (!node || !sh || node->u_data.redirection.direction == HEREDOC)
		return ;
	expanded_args = NULL;
	str = node->u_data.redirection.file;
	arg_expansion(str, &expanded_args, sh);
	if (ft_lstsize_token(expanded_args) != 1
		|| !ft_strcmp(expanded_args->value, ""))
		error("wrong redirection", NULL, 1, sh);
	else
	{
		tmp = ft_strdup(expanded_args->value);
		node->u_data.redirection.file = tmp;
		node->u_data.redirection.file_free = true;
	}
	free_token_list(expanded_args);
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
