/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:43:03 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/25 02:48:17 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_out_redirection(t_ast_redir *last_redir, t_shell *sh)
{
	int		output_fd;
	int		original_stdout;
	t_ast	*cmd_node;
	int		status;

	output_fd = open_redirection_file(last_redir->file, O_WRONLY
			| O_CREAT | O_TRUNC, sh);
	original_stdout = dup(STDOUT_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	cmd_node = last_redir->command;
	status = EXIT_SUCCESS;
	if (cmd_node)
		status = execute(cmd_node, KEEP_RUNNING, sh);
	if (sh->is_parent && original_stdout != -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	return (status);
}

static int	execute_node(t_ast *node, t_exit end, t_shell *sh)
{
	int	status;

	status = EXIT_FAILURE;
	if (sh->redirection_error_out)
	{
		sh->last_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == AST_COMMAND || node->type == AST_REDIRECTION)
		node_expansion(node, sh);
	if (node->type == AST_LOGICAL)
		status = exec_logical(&node->u_data.logical, sh);
	else if (node->type == AST_PIPELINE)
		status = exec_pipeline(node, sh);
	else if (node->type == AST_REDIRECTION)
		status = exec_redirection(&node->u_data.redirection, sh);
	else if (node->type == AST_SUBSHELL)
		status = exec_subshell(&node->u_data.subshell, sh);
	else if (node->type == AST_COMMAND)
	{
		if (!sh->redirection_error)
			status = exec_command(&node->u_data.command, end, sh);
		else
			status = EXIT_FAILURE;
	}
	return (status);
}

int	execute(t_ast *node, t_exit end, t_shell *sh)
{
	int		status;
	bool	had_redirection_error;

	(void)end;
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == AST_PIPELINE)
	{
		had_redirection_error = sh->redirection_error;
		status = execute_node(node, end, sh);
		if (had_redirection_error)
			sh->redirection_error = true;
	}
	else
		status = execute_node(node, end, sh);
	if (node->type != AST_PIPELINE || !sh->redirection_error)
		sh->redirection_error = false;
	return (status);
}
