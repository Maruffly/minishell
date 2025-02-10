/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:44:28 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/10 17:04:07 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_input(t_ast_redirection *redir, t_shell *sh)
{
	int	status;
	int	input_fd;
	int	original_stdin;

	input_fd = open(redir->file, O_RDONLY);
	if (input_fd == -1)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		perror(redir->file);
		return (EXIT_FAILURE);
	}
	original_stdin = dup(STDIN_FILENO);
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	status = execute(redir->command, KEEP_RUNNING, sh);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	return (status);
}

int	redirect_output(t_ast_redirection *redir, t_shell *sh)
{
	int	status;
	int	output_fd;
	int	original_stdout;

	output_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
	{
		write(STDERR_FILENO, "Omar&Fred: ", 11);
		perror(redir->file);
		return (EXIT_FAILURE);
	}
	original_stdout = dup(STDOUT_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	status = execute(redir->command, KEEP_RUNNING, sh);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	return (status);
}

int	append_output(t_ast_redirection *redir, t_shell *sh)
{
	int	status;
	int	output_fd;
	int	original_stdout;

	output_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (output_fd == -1)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		perror(redir->file);
		return (EXIT_FAILURE);
	}
	original_stdout = dup(STDOUT_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	status = execute(redir->command, KEEP_RUNNING, sh);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	return (status);
}

int	redirect_heredoc(t_ast_redirection *redir, t_shell *sh)
{
	int		status;
	int		original_stdin;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
	{
		perror("dup");
		return (EXIT_FAILURE);
	}
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(original_stdin);
		return (EXIT_FAILURE);
	}
	status = execute(redir->command, KEEP_RUNNING, sh);
	if (dup2(original_stdin, STDIN_FILENO))
	{
		perror("dup2");
		close(original_stdin);
		exit (EXIT_FAILURE);
	}
	close (original_stdin);
	return (status);
}

int	exec_redirection(t_ast_redirection *redir, t_shell *sh)
{
	int	status;

	status = EXIT_FAILURE;
	if (redir->direction == REDIRECT_IN)
		status = redirect_input(redir, sh);
	else if (redir->direction == HEREDOC)
		status = redirect_heredoc(redir, sh);
	else if (redir->direction == REDIRECT_OUT)
		status = redirect_output(redir, sh);
	else if (redir->direction == APPEND_OUT)
		status = append_output(redir, sh);
	return (status);
}
