/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:58:31 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 20:26:24 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redir_input(t_ast_redirection *redir, t_shell *sh)
{
	int	input_fd;
	int	original_stdin;
	int	status;

	input_fd = open(redir->file, O_RDONLY);
	if (input_fd == -1)
		return (report_errno(redir->file, sh));
	original_stdin = dup(STDIN_FILENO);
	dup2_s(input_fd, STDIN_FILENO, sh);
	close_s(input_fd, sh);
	status = execute(redir->child, O_RETURN, sh);
	dup2(original_stdin, STDIN_FILENO);
	close_s(original_stdin, sh);
	return (status);
}

static int	redir_output(t_ast_redirection *redir, t_shell *sh)
{
	int	output_fd;
	int	original_stdout;
	int	status;

	output_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		return (report_errno(redir->file, sh));
	original_stdout = dup(STDOUT_FILENO);
	dup2_s(output_fd, STDOUT_FILENO, sh);
	close_s(output_fd, sh);
	status = execute(redir->child, O_RETURN, sh);
	dup2_s(original_stdout, STDOUT_FILENO, sh);
	close_s(original_stdout, sh);
	return (status);
}

static int	append_output(t_ast_redirection *redir, t_shell *sh)
{
	int	output_fd;
	int	original_stdout;
	int	status;

	output_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (output_fd == -1)
		return (report_errno(redir->file, sh));
	original_stdout = dup(STDOUT_FILENO);
	dup2_s(output_fd, STDOUT_FILENO, sh);
	close_s(output_fd, sh);
	status = execute(redir->child, O_RETURN, sh);
	dup2_s(original_stdout, STDOUT_FILENO, sh);
	close_s(original_stdout, sh);
	return (status);
}

int	exec_redir(t_ast_redirection *redir, t_shell *sh)
{
	int	status;

	status = EXIT_FAILURE;
	if (redir->direction == REDIRECT_IN || redir->direction == HEREDOC)
		status = redir_input(redir, sh);
	else if (redir->direction == REDIRECT_OUT)
		status = redir_output(redir, sh);
	else if (redir->direction == APPEND_OUT)
		status = append_output(redir, sh);
	return (status);
}
