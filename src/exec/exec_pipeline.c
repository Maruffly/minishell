/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:43:03 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/25 10:26:13 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*build_cmd_list(t_ast *node, t_shell *sh)
{
	t_token	*pipeline;
	t_ast	*right;
	t_ast	*left;

	pipeline = NULL;
	while (node->type == AST_PIPELINE)
	{
		right = node->u_data.pipeline.right;
		add_front_token(&pipeline, right, sh);
		if (right->type == AST_COMMAND)
			pipeline->value = right->u_data.command.args[0];
		left = node->u_data.pipeline.left;
		if (!left)
			return (NULL);
		if (left->type == AST_PIPELINE)
			node = left;
		else
		{
			add_front_token(&pipeline, left, sh);
			if (left->type == AST_COMMAND)
				pipeline->value = left->u_data.command.args[0];
			break ;
		}
	}
	return (pipeline);
}

static pid_t	exec_one_pipeline_token(t_token *pipeline, int prev_read_end,
				int p[2], t_shell *sh)
{
	pid_t	pid;

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
	}
	close(p[0]);
	close(p[1]);
	execute((t_ast *)pipeline->node, KEEP_RUNNING, sh);
	exit(sh->last_status);
}

static int	exec_single_process(t_token *pipeline, int prev_read_end,
								int p[2], t_shell *sh)
{
	pid_t	last_pid;

	last_pid = exec_one_pipeline_token(pipeline, prev_read_end, p, sh);
	if (sh->redirection_error)
		sh->redirection_error = false;
	if (prev_read_end != -1)
		close(prev_read_end);
	close(p[1]);
	return (p[0]);
}

static int	exec_pipeline_token(t_token *pipeline, t_shell *sh)
{
	int		p[2];
	pid_t	last_pid;
	int		prev_read_end;
	int		n_pipeline;
	t_token	*last_cmd;

	last_cmd = NULL;
	n_pipeline = ft_lstsize_token(pipeline) - 1;
	last_pid = 0;
	prev_read_end = -1;
	last_cmd = pipeline;
	while (last_cmd && last_cmd->next)
		last_cmd = last_cmd->next;
	while (pipeline)
	{
		if (pipe(p) == -1)
			return (EXIT_FAILURE);
		prev_read_end = exec_single_process(pipeline, prev_read_end, p, sh);
		pipeline = pipeline->next;
	}
	if (prev_read_end != -1)
		close(prev_read_end);
	return (wait_for_children(last_pid, n_pipeline, sh));
}

int	exec_pipeline(t_ast *node, t_shell *sh)
{
	int		status;
	pid_t	last_pid;
	t_token	*cmd_list;

	status = 0;
	cmd_list = build_cmd_list(node, sh);
	if (!cmd_list)
		return (EXIT_FAILURE);
	last_pid = exec_pipeline_token(cmd_list, sh);
	if (last_pid == -1)
	{
		free_list_token(cmd_list);
		return (EXIT_FAILURE);
	}
	free_list_token(cmd_list);
	return (WEXITSTATUS(status));
}
