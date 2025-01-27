/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:05:31 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/27 17:53:26 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static t_token	*build_cmd_list(t_ast *node, t_shell *sh)
{
	t_token *pipeline;

	pipeline = NULL;
	while (node->type == AST_PIPELINE)
	{
		add_front_token(&pipeline, node->u_data.pipeline.right, sh);
		if (node->u_data.pipeline.right->type == AST_COMMAND)
			pipeline->value = node->u_data.pipeline.right->u_data.command.args[0];
		if (node->u_data.pipeline.left->type == AST_PIPELINE)
			node = node->u_data.pipeline.left;
		else
		{
			add_front_token(&pipeline, node->u_data.pipeline.left, sh);
			if (node->u_data.pipeline.left->type == AST_COMMAND)
				pipeline->value = node->u_data.pipeline.left->u_data.command.args[0];
			break;
		}
	}
	return (pipeline);
}

static pid_t	exec_one_pipeline_token(t_token *pipeline, int prev_read_end, int p[2],
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

static int	exec_pipeline_token(t_token *pipeline, t_shell *sh)
{
	int		p[2];
	pid_t	last_pid;
	int		n_pipeline;
	int		prev_read_end;
	int		last_cmd_status;

	n_pipeline = ft_lstsize_token(pipeline) - 1;
	last_pid = 0;
	prev_read_end = -1;
	while (pipeline)
	{
		pipe(p);
		last_pid = exec_one_pipeline_token(pipeline, prev_read_end, p, sh);
		setup_for_next_command(&prev_read_end, p, sh);
		pipeline = pipeline->next;
	}
	last_cmd_status = wait_for_children(last_pid, n_pipeline, sh);
	return (last_cmd_status);
}

int	exec_pipeline(t_ast *node, t_shell *sh)
{
	t_token *pipeline;

	pipeline = build_cmd_list(node, sh);
	if (!pipeline)
		return (EXIT_FAILURE);
	return (exec_pipeline_token(pipeline, sh));
}
