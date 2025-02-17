/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:16:37 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/17 12:31:40 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_ast_cmd(char **args)
{
	t_ast	*node;

	init_ast_node(&node, AST_COMMAND);
	node->u_data.command.args = args;
	return (node);
}

t_ast	*create_ast_subshell(t_ast *child, t_shell *sh)
{
	t_ast	*node;

	if (!child)
		return (syntax_error("(", sh));
	init_ast_node(&node, AST_SUBSHELL);
	node->u_data.subshell.child = child;
	return (node);
}

t_ast	*create_ast_redirection(t_token_type direction, t_token *filename,
		t_ast *command, t_shell *sh)
{
	t_ast	*node;

	if (!filename || !is_word(filename))
		return (syntax_error(get_token_string(direction), sh));
	init_ast_node(&node, AST_REDIRECTION);
	node->u_data.redirection.direction = direction;
	node->u_data.redirection.file = ft_strdup(filename->value);
	node->u_data.redirection.command = command;
	return (node);
}

t_ast	*create_ast_pipeline(t_ast	*left, t_ast *right, t_shell *sh)
{
	t_ast	*node;

	if (!left || !right)
		return (syntax_error("|", sh));
	init_ast_node(&node, AST_PIPELINE);
	node->u_data.pipeline.left = left;
	node->u_data.pipeline.right = right;
	return (node);
}

t_ast	*create_ast_logical(t_ast *left, t_token_type op, t_ast *right,
		t_shell *sh)
{
	t_ast	*node;

	if (!left || !right)
		return (syntax_error(get_token_string(op), sh));
	init_ast_node(&node, AST_LOGICAL);
	node->u_data.logical.operator = op;
	node->u_data.logical.left = left;
	node->u_data.logical.right = right;
	return (node);
}
