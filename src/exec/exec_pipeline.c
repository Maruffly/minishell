/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/24 17:52:33 by jlaine           ###   ########.fr       */
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
	int		num_processes;

	n_pipeline = ft_lstsize_token(pipeline) - 1;
	last_pid = 0;
	prev_read_end = -1;
	num_processes = 0;
	while (pipeline)
	{
		if (pipe(p) == -1)
			return (EXIT_FAILURE);
		last_pid = exec_one_pipeline_token(pipeline, prev_read_end, p, sh);
		if (prev_read_end != -1)
			close(prev_read_end);
		close(p[1]);
		prev_read_end = p[0];
		pipeline = pipeline->next;
	}
	if (prev_read_end != -1)
		close(prev_read_end);
	last_cmd_status = wait_for_children(last_pid, n_pipeline, sh);
	return (last_cmd_status);
}

// int	exec_pipeline(t_ast *node, t_shell *sh)
// {
// 	t_token	*pipeline;
// 	int		status;

// 	pipeline = build_cmd_list(node, sh);
// 	if (!pipeline)
// 		return (EXIT_FAILURE);
// 	if (sh->redirection_error)
// 	{
// 		sh->redirection_error = false;
// 		free_list_token(pipeline);
// 		return (EXIT_FAILURE);
// 	}
// 	status = exec_pipeline_token(pipeline, sh);
// 	free_list_token(pipeline);
// 	return (status);
// }

void free_cmd_list(t_ast *cmd_list)
{
    t_ast *tmp;

    while (cmd_list)
    {
        tmp = cmd_list->u_data.pipeline.right; // Accéder au prochain élément
        free(cmd_list);
        cmd_list = tmp;
    }
}


int exec_pipeline(t_ast *node, t_shell *sh)
{
    t_token *cmd_list;
    int status;
    pid_t last_pid;

    // 🔹 Construire la liste des commandes du pipeline
    cmd_list = build_cmd_list(node, sh);
    if (!cmd_list)
        return (EXIT_FAILURE);

    // 🔹 Exécuter les commandes du pipeline
    last_pid = exec_pipeline_token(cmd_list, sh);
    if (last_pid == -1)
	{
		return (EXIT_FAILURE);
		free_list_token(cmd_list);
	}
        // return (EXIT_FAILURE);

    // ✅ Attendre tous les processus enfants pour éviter un prompt vide
    while (waitpid(-1, &status, 0) > 0);

	free_list_token(cmd_list);
    return WEXITSTATUS(status);
}
