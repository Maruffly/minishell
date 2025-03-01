/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:43:03 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 09:53:39 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_for_next_command(int *prev_read_end, int p[2], t_shell *sh)
{
	if (*prev_read_end != -1)
		safe_close(*prev_read_end, sh);
	safe_close(p[WRITE], sh);
	*prev_read_end = p[READ];
}

int	wait_for_children(pid_t last_pid, int n_pipeline, t_shell *sh)
{
	pid_t	child_pid;
	int		status;
	int		last_cmd_status;
	bool	new_line;

	new_line = false;
	last_cmd_status = 0;
	while (n_pipeline--)
	{
		child_pid = safe_wait(&status, sh);
		if (child_pid == last_pid)
			last_cmd_status = check_process_child_exit(status, &new_line, sh);
		else
			check_process_child_exit(status, &new_line, sh);
	}
	return (last_cmd_status);
}
