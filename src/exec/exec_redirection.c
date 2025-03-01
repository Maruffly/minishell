/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:58:31 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 09:44:20 by jlaine           ###   ########.fr       */
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
	safe_dup2(input_fd, STDIN_FILENO, sh);
	safe_close(input_fd, sh);
	status = execute(redir->child, O_RETURN, sh);
	dup2(original_stdin, STDIN_FILENO);
	safe_close(original_stdin, sh);
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
	safe_dup2(output_fd, STDOUT_FILENO, sh);
	safe_close(output_fd, sh);
	status = execute(redir->child, O_RETURN, sh);
	safe_dup2(original_stdout, STDOUT_FILENO, sh);
	safe_close(original_stdout, sh);
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
	safe_dup2(output_fd, STDOUT_FILENO, sh);
	safe_close(output_fd, sh);
	status = execute(redir->child, O_RETURN, sh);
	safe_dup2(original_stdout, STDOUT_FILENO, sh);
	safe_close(original_stdout, sh);
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
