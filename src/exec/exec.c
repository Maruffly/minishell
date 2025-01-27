/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:33:30 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/27 17:56:46 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	execute(t_ast *node, t_exit end, t_shell *sh)
{
	int	status;

	(void)end; 
	status = 0;
	if (!node)
		return (EXIT_SUCCESS);
	if (node->type == AST_COMMAND || node->type == AST_REDIRECTION)
		node_expansion(node, sh);
	if (node->type == AST_LOGICAL)
		status = exec_logical(&node->u_data.logical, sh);
	else if (node->type == AST_PIPELINE)
		status = exec_pipeline(node, sh);
	else if (node->type == AST_REDIRECTION)
		status = exec_redirection(&node->u_data.redirection, sh);
	else if (node->type == AST_SUBSHELL)
		status = exec_subshell(&node->u_data.subshell, sh);
	else if (node->type == AST_COMMAND)
		status = exec_command(&node->u_data.command, end, sh);
	return (status);
}
