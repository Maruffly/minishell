/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:22:15 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 11:28:34 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*expand_node(t_ast *node, t_shell *sh)
{
	if (node->type == AST_COMMAND)
		expand_command(node, sh);
	else if (node->type == AST_REDIRECTION)
		expand_redirection(node, sh);
	return (node);
}

void	expand_command(t_ast *node, t_shell *sh)
{
	char	**args;
	t_list	*expanded_args;

	expanded_args = NULL;
	args = node->u_data.command.args;
	while (*args)
	{
		exp_single_arg(*args, &expanded_args, sh);
		args++;
	}
	node->u_data.command.args = convert_list_to_array(&expanded_args, sh);
}

void	expand_redirection(t_ast *node, t_shell *sh)
{
	char	*str;
	t_list	*expanded_args;

	if (node->u_data.redirection.direction == HEREDOC)
		return ;
	expanded_args = NULL;
	str = node->u_data.redirection.file;
	exp_single_arg(str, &expanded_args, sh);
	if (ft_lstsize(expanded_args) != 1 || !ft_strcmp(expanded_args->content,
			""))
		report_error("redirection:", NULL, " ambiguous redirect", sh);
	else
		node->u_data.redirection.file = expanded_args->content;
}
