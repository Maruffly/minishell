/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:05:31 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/09 17:21:36 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_token	*build_cmd_list(t_ast *node, t_shell *sh)
{
	t_token *pipeline;

	pipeline = NULL;
	while (node->type == AST_PIPELINE)
	{
		add_front_token(&pipeline, node->u_data.pipeline.right, sh);
		if (node->u_data.pipeline.left->type == AST_PIPELINE)
			node = node->u_data.pipeline.left;
		else
		{
			add_front_token(&pipeline, node->u_data.pipeline.left, sh);
			break;
		}
	}
	return (pipeline);
}

int	execute_pipeline_token(t_token *pipeline, t_shell *sh)
{
	int     p[2];
	pid_t   last_pid;
	int     n_pipeline;
	int     prev_read_end;
	int     last_cmd_status;

	n_pipeline = ft_lstsize_token(pipeline);
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
	return (execute_pipeline_token(pipeline, sh));
}
