/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:43:03 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 09:53:21 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*build_cmd_list(t_ast *node, t_shell *sh)
{
	t_list	*pipeline;

	pipeline = NULL;
	while (node->type == AST_PIPELINE)
	{
		safe_lst_addfront(node->u_data.pipeline.right, &pipeline, PROMPT, sh);
		if (node->u_data.pipeline.left->type == AST_PIPELINE)
			node = node->u_data.pipeline.left;
		else
		{
			safe_lst_addfront(node->u_data.pipeline.left, &pipeline, PROMPT, sh);
			break ;
		}
	}
	return (pipeline);
}

static pid_t	exec_single_pipeline(t_list *pipeline, int prev_read_end,
		int p[2], t_shell *sh)
{
	pid_t	pid;

	pid = safe_fork(sh);
	if (pid != 0)
		return (pid);
	sh->in_main_process = false;
	set_signal_child_process();
	if (prev_read_end != -1)
	{
		safe_dup2(prev_read_end, STDIN_FILENO, sh);
		safe_close(prev_read_end, sh);
	}
	if (pipeline->next != NULL)
		safe_dup2(p[WRITE], STDOUT_FILENO, sh);
	safe_close(p[READ], sh);
	safe_close(p[WRITE], sh);
	execute((t_ast *)pipeline->content, O_EXIT, sh);
	return (pid);
}

static int	exec_pipeline_list(t_list *pipeline, t_shell *sh)
{
	int		p[2];
	int		prev_read_end;
	pid_t	last_pid;
	int		last_cmd_status;
	int		n_pipeline;

	n_pipeline = ft_lstsize(pipeline);
	last_pid = 0;
	prev_read_end = -1;
	while (pipeline)
	{
		safe_pipe(p, sh);
		last_pid = exec_single_pipeline(pipeline, prev_read_end, p, sh);
		setup_for_next_command(&prev_read_end, p, sh);
		pipeline = pipeline->next;
	}
	last_cmd_status = wait_for_children(last_pid, n_pipeline, sh);
	return (last_cmd_status);
}

int	exec_pipeline(t_ast *node, t_shell *sh)
{
	t_list	*pipeline;

	pipeline = build_cmd_list(node, sh);
	return (exec_pipeline_list(pipeline, sh));\
}
