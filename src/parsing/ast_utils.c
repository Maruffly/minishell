/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:37:13 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/11 17:53:13 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*get_last_child_redir(t_ast *node)
{
	while (node && node->type == AST_REDIRECTION
	&& node->u_data.redirection.child
	&& node->u_data.redirection.child->type == AST_REDIRECTION)
	node = node->u_data.redirection.child;
	return (node);
}

t_ast	*build_redir_cmd(t_ast *prefix, t_ast *suffix, t_ast *command)
{
	t_ast	*last_child;

	if (prefix && suffix)
	{
		last_child = get_last_child_redir(prefix);
		last_child->u_data.redirection.child = suffix;
		last_child = get_last_child_redir(suffix);
		last_child->u_data.redirection.child = command;
		return (prefix);
	}
	else if (!prefix && suffix)
	{
		last_child = get_last_child_redir(suffix);
		last_child->u_data.redirection.child = command;
		return (suffix);
	}
	else if (prefix && !suffix)
	{
		last_child = get_last_child_redir(prefix);
		last_child->u_data.redirection.child = command;
		return (prefix);
	}
	else
		return (command);
}

t_ast	*get_last_child_redir(t_ast *node)
{
	while (node && node->type == AST_REDIRECTION
	&& node->u_data.redirection.child
	&& node->u_data.redirection.child->type == AST_REDIRECTION)
	node = node->u_data.redirection.child;
	return (node);
}

