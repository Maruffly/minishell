/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:16:37 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 10:09:01 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_ast_command(char **argv, t_shell *sh)
{
	t_ast	*node;

	init_ast_node(&node, AST_COMMAND, sh);
	node->u_data.command.args = argv;
	return (node);
}

t_ast	*create_ast_subshell(t_ast *child, t_shell *sh)
{
	t_ast	*node;

	if (!child)
		return (set_syntax_error("(", sh));
	init_ast_node(&node, AST_SUBSHELL, sh);
	node->u_data.subshell.child = child;
	return (node);
}

t_ast	*create_ast_redirection(t_token_type direction, t_list *filename,
		t_ast *child, t_shell *sh)
{
	t_ast	*node;

	if (!filename || type(filename) != WORD)
		return (set_syntax_error(type_to_string(direction), sh));
	init_ast_node(&node, AST_REDIRECTION, sh);
	node->u_data.redirection.direction = direction;
	node->u_data.redirection.file = value(filename);
	node->u_data.redirection.child = child;
	return (node);
}

t_ast	*create_ast_pipeline(t_ast *left, t_ast *right, t_shell *sh)
{
	t_ast	*node;

	if (!left || !right)
		return (set_syntax_error("|", sh));
	init_ast_node(&node, AST_PIPELINE, sh);
	node->u_data.pipeline.left = left;
	node->u_data.pipeline.right = right;
	return (node);
}

t_ast	*create_ast_logical(t_ast *left, t_token_type operator, t_ast *right,
	t_shell *sh)
{
	t_ast	*node;

	if (!left || !right)
		return (set_syntax_error(type_to_string(operator), sh));
	init_ast_node(&node, AST_LOGICAL, sh);
	node->u_data.logical.operator = operator;
	node->u_data.logical.left = left;
	node->u_data.logical.right = right;
	return (node);
}
