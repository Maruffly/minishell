/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:05:31 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/23 23:27:49 by jbmy             ###   ########.fr       */
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

static int	exec_pipeline_token(t_token *pipeline, t_shell *sh)
{
	int		p[2];
	pid_t	last_pid;
	int		n_pipeline;
	int		prev_read_end;
	int		last_cmd_status;

	/*print_open_fds("Start of pipeline");*/
	n_pipeline = ft_lstsize_token(pipeline) - 1;
	last_pid = 0;
	prev_read_end = -1;
	while (pipeline)
	{
		if (pipe(p) == -1)
			return (EXIT_FAILURE);
		/*print_open_fds("Before fork");*/
		last_pid = exec_one_pipeline_token(pipeline, prev_read_end, p, sh);
		/* if (last_pid > 0)  // Parent process
        {
            char cmd_name[256];
            snprintf(cmd_name, sizeof(cmd_name), "Pipeline cmd: %s", 
                    pipeline->value ? pipeline->value : "unknown");
            trace_child_fds(cmd_name, last_pid);  // Debug
        } */
		if (prev_read_end != -1)
			close(prev_read_end);
		close(p[1]);
		prev_read_end = p[0];
		/*print_open_fds("After fork and pipe setup");*/
		pipeline = pipeline->next;
	}
	if (prev_read_end != -1)
		close(prev_read_end);
	/*print_open_fds("Before waiting for children");*/
	last_cmd_status = wait_for_children(last_pid, n_pipeline, sh);
	/*print_open_fds("End of pipeline");*/
	return (last_cmd_status);
}

int	exec_pipeline(t_ast *node, t_shell *sh)
{
	t_token	*pipeline;
	int		status;

	pipeline = build_cmd_list(node, sh);
	if (!pipeline)
		return (EXIT_FAILURE);
	if (sh->redirection_error)
	{
		sh->redirection_error = false;
		free_list_token(pipeline);
		return (EXIT_FAILURE);
	}
	status = exec_pipeline_token(pipeline, sh);
	free_list_token(pipeline);
	return (status);
}
