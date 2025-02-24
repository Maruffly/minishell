/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/24 15:27:07 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	check_process_child_exit(int status, bool *new_line, t_shell *sh)
{
	int	signal;

	(void)sh;
	if (status == 0)
		return (EXIT_SUCCESS);
	if (status < 0)
		return (EXIT_FAILURE);
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

pid_t	exec_one_pipeline_token(t_token *pipeline, int prev_read_end, int p[2],
		t_shell *sh)
{
	pid_t	pid;

	/* if (sh->redirection_error)
	{
		close(p[0]);
		close(p[1]);
		if (prev_read_end != -1)
			close(prev_read_end);
		return (-1);
	} */
	pid = fork();
	if (pid != 0)
		return (pid);
	sh->is_parent = false;
	set_child_signals();
	if (prev_read_end != -1)
	{
		if (dup2(prev_read_end, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(prev_read_end);
	}
	if (pipeline->next != NULL)
	{
		if (dup2(p[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(p[1]);
	}
	close(p[0]);
	execute((t_ast *)pipeline->node, KEEP_RUNNING, sh);
	exit(sh->last_status);
}

int	wait_for_children(pid_t last_pid, int n_pipeline, t_shell *sh)
{
	pid_t	child_pid;
	int		status;
	int		last_cmd_status;
	bool	new_line;

	new_line = false;
	last_cmd_status = 0;
	while (n_pipeline > 0)
	{
		child_pid = waitpid(-1, &status, 0);
		if (child_pid == -1)
			break ;
		if (child_pid == last_pid)
			last_cmd_status = check_process_child_exit(status, &new_line, sh);
		else
			check_process_child_exit(status, &new_line, sh);
		n_pipeline--;
		n_pipeline--;
	}
	return (last_cmd_status);
}
