/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:00:17 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 21:12:40 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast	*get_last_redir_list(t_ast *node)
{
	while (node && node->type == AST_REDIRECTION
		&& node->u_data.redirection.child
		&& node->u_data.redirection.child->type == AST_REDIRECTION)
		node = node->u_data.redirection.child;
	return (node);
}

t_ast	*build_redirected_command(t_ast *prefix, t_ast *suffix, t_ast *command)
{
	if (prefix && suffix)
	{
		get_last_redir_list(prefix)->u_data.redirection.child = suffix;
		get_last_redir_list(suffix)->u_data.redirection.child = command;
		return (prefix);
	}
	else if (prefix && !suffix)
	{
		get_last_redir_list(prefix)->u_data.redirection.child = command;
		return (prefix);
	}
	else if (!prefix && suffix)
	{
		get_last_redir_list(suffix)->u_data.redirection.child = command;
		return (suffix);
	}
	else
		return (command);
}
