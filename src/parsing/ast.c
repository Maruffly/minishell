/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/11 17:22:29 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_ast_node(t_ast **node, t_ast_type type)
{
	*node = ft_calloc(1, sizeof(t_ast));
	(*node)->is_freed = false;
	(*node)->type = type;
	/* if (type == AST_COMMAND)
		(*node)->u_data.command.args = NULL;
	else if (type == AST_REDIRECTION)
	{
		(*node)->u_data.redirection.file = NULL;
		(*node)->u_data.redirection.command = NULL;
	} 
	else if (type == AST_PIPELINE) 
	{
		(*node)->u_data.pipeline.left = NULL;
		(*node)->u_data.pipeline.right = NULL;
	} 
	else if (type == AST_LOGICAL) 
	{
		(*node)->u_data.logical.left = NULL;
		(*node)->u_data.logical.right = NULL;
	} 
	else if (type == AST_SUBSHELL) {
		(*node)->u_data.subshell.child = NULL;
	} */
}
