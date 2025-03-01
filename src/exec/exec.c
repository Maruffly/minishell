/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:43:03 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 09:58:08 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute(t_ast *node, t_execute_end end, t_shell *sh)
{
	int	status;

	if (!node)
		return (EXIT_SUCCESS);
	if (node->type == AST_REDIRECTION || node->type == AST_COMMAND)
		expand_node(node, sh);
	if (node->type == AST_LOGICAL)
		status = execute_logical(&node->u_data.logical, sh);
	else if (node->type == AST_PIPELINE)
		status = exec_pipeline(node, sh);
	else if (node->type == AST_REDIRECTION)
		status = exec_redir(&node->u_data.redirection, sh);
	else if (node->type == AST_SUBSHELL)
		status = exec_subshell(&node->u_data.subshell, sh);
	else if (node->type == AST_COMMAND)
		status = exec_cmd(&node->u_data.command, end, sh);
	else
		error("execute", "illegal node type", EXIT_FAILURE, sh);
	if (end == O_EXIT)
		exit(status);
	return (status);
}

int	check_process_child_exit(int status, bool *new_line, t_shell *sh)
{
	int	signal;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putstr_fd("Quit: core dumped", STDERR_FILENO);
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
