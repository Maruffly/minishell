/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/18 10:56:59 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_ast_node(t_ast **node, t_ast_type type)
{
	*node = ft_calloc(1, sizeof(t_ast));
	if (!(*node))
		return ;
	(*node)->type = type;
	(*node)->is_freed = false;
}

t_ast	*get_last_command_redir(t_ast *node)
{
	while (node && node->type == AST_REDIRECTION
		&& node->u_data.redirection.command
		&& node->u_data.redirection.command->type == AST_REDIRECTION)
	node = node->u_data.redirection.command;
	return (node);
}

t_ast	*build_redir_cmd(t_ast *prefix, t_ast *suffix, t_ast *command)
{
	t_ast	*last_command;

	if (prefix && suffix)
	{
		last_command = get_last_command_redir(prefix);
		last_command->u_data.redirection.command = suffix;
		last_command = get_last_command_redir(suffix);
		last_command->u_data.redirection.command = command;
		return (prefix);
	}
	else if (!prefix && suffix)
	{
		last_command = get_last_command_redir(suffix);
		last_command->u_data.redirection.command = command;
		return (suffix);
	}
	else if (prefix && !suffix)
	{
		last_command = get_last_command_redir(prefix);
		last_command->u_data.redirection.command = command;
		return (prefix);
	}
	else
		return (command);
}
