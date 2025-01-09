/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:33:30 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/09 17:44:04 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	check_process_child_exit(int status, bool *new_line, t_shell *sh)
{
	int	signal;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putstr_fd("Quit: 3", STDERR_FILENO);
		if (signal == SIGQUIT || signal == SIGINT)
		{
			if (!new_line || (new_line && *new_line == false))
				ft_putstr_fd("\n", STDERR_FILENO);
			if (new_line && *new_line == false)
				*new_line = true;
		}
		return (128 + signal);
	}
	else
		return (EXIT_FAILURE);
}

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
		status = exec_redirection(&node->u_data.redirection, sh); //// TO DO
	return (status);
}
