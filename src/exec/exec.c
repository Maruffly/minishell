/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:33:30 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/08 18:51:19 by jmaruffy         ###   ########.fr       */
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
	/* else if (node->type == AST_PIPELINE) */
		
	return (status);
}
