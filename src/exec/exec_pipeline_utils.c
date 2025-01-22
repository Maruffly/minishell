/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:44:13 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/22 15:30:48 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

pid_t	exec_one_pipeline_token(t_token *pipeline, int prev_read_end, int p[2],
		t_shell *sh)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0) // PB : avec 1 pipe, le programme devrait executer dans le parent.
		return (pid);
	sh->is_parent = false;
	set_child_signals();
	if (prev_read_end != -1)
	{
		dup2(prev_read_end, STDIN_FILENO);
		close(prev_read_end);
	}
	if (pipeline->next != NULL)
		dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(p[1]);
	execute((t_ast *)pipeline->node, KEEP_RUNNING, sh);
	exit(sh->last_status);
}

void	setup_for_next_command(int *prev_read_end, int p[2], t_shell *sh)
{
	(void)sh;

	if (*prev_read_end != -1)
		close(*prev_read_end);
	close(p[1]);
	*prev_read_end = p[0];
}

int	wait_for_children(pid_t last_pid, int n_pipeline, t_shell *sh)
{
	pid_t	child_pid;
	int		status;
	int		last_cmd_status;
	bool	new_line;

	new_line = false;
	last_cmd_status = 0;
	while (n_pipeline-- >= 0) // testtt
	{
		child_pid = wait(&status);
		if (child_pid == last_pid)
			last_cmd_status = check_process_child_exit(status, &new_line, sh);
		else
			check_process_child_exit(status, &new_line, sh);
	}
	return (last_cmd_status);
}
