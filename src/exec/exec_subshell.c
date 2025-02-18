/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:43:03 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/18 11:56:03 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_subshell(t_ast_subshell *subshell, t_shell *sh)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Omar&Fred: fork error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		sh->is_parent = false;
		set_child_signals();
		exit(execute(subshell->child, EXIT_SHELL, sh));
	}
	else
	{
		waitpid(pid, &status, 0);
		status = check_process_child_exit(status, NULL, sh);
	}
	return (status);
}
