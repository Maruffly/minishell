/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:43:03 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 19:50:51 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_for_next_command(int *prev_read_end, int p[2], t_shell *sh)
{
	if (*prev_read_end != -1)
		close_s(*prev_read_end, sh);
	close_s(p[WRITE_END], sh);
	*prev_read_end = p[READ_END];
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
		child_pid = wait_s(&status, sh);
		if (child_pid == last_pid)
			last_cmd_status = check_process_child_exit(status, &new_line, sh);
		else
			check_process_child_exit(status, &new_line, sh);
	}
	return (last_cmd_status);
}
