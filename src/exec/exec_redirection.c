/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:44:28 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/13 14:14:51 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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

int	exec_redirection(t_ast_redirection *redir, t_shell *sh)
{
	int	status;

	status = EXIT_FAILURE;
	if (redir->direction == REDIRECT_IN || redir->direction == HEREDOC)
		status = redirect_input(redir, sh);
	else if (redir->direction == REDIRECT_OUT)
		status = redirect_output(redir, sh);
	else if (redir->direction == APPEND_OUT)
		status = append_output(redir, sh);
	return (status);
}
