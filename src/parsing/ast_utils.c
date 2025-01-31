/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:37:13 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/31 18:09:55 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
