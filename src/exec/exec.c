/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:33:30 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/07 15:41:17 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	execute(t_ast *node, t_exit end, t_shell *sh)
{
	int	status = 0;

	(void)end;
	if (!node)
		return (EXIT_SUCCESS);
	if (node->type == AST_COMMAND || node->type == AST_REDIRECTION)
		node_expansion(node, sh);
	return (status);
}
