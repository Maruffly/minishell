/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:02 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/24 18:54:00 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	write_to_pipe(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1
		|| write(fd, "\n", 1) == -1)
		return (false);
	return (true);
}

int	heredoc_eof_handler(t_heredoc *hdoc)
{
	static int	line_count = 1;
	char		*line_str;

	line_str = ft_itoa(line_count++);
	if (!line_str)
		return (EXIT_FAILURE);
	ft_putstr_fd("\nOmar&Fred: warning: here-document at line ", 2);
	ft_putstr_fd(line_str, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(hdoc->limiter, 2);
	ft_putstr_fd("')\n", 2);
	free(line_str);
	return (EXIT_SUCCESS);
}

static t_heredoc	*init_heredoc(char *delimiter)
{
	t_heredoc	*hdoc;

	hdoc = ft_calloc(1, sizeof(t_heredoc));
	if (!hdoc)
		return (NULL);
	hdoc->limiter = ft_strdup(delimiter);
	if (!hdoc->limiter)
	{
		free(hdoc);
		return (NULL);
	}
	hdoc->expand_vars = !is_quoted(delimiter);
	if (!hdoc->expand_vars)
		remove_quotes(hdoc->limiter);
	hdoc->saved_stdout = 0;
	hdoc->bytes_read = 0;
	return (hdoc);
}

int	handle_heredoc(t_ast_redir *redir, t_shell *sh, t_expand *exp)
{
	t_heredoc	*hdoc;
	int			error_code;

	hdoc = init_heredoc(redir->file);
	if (!hdoc)
		return (EXIT_FAILURE);
	if (pipe(hdoc->pipe_fd) == -1)
	{
		free_heredoc(hdoc);
		return (perror("heredoc pipe"), EXIT_FAILURE);
	}
	error_code = read_heredoc(hdoc, sh, exp);
	if (error_code != EXIT_SUCCESS)
	{
		close(hdoc->pipe_fd[0]);
		close(hdoc->pipe_fd[1]);
		free_heredoc(hdoc);
		return (error_code);
	}
	redir->heredoc_fd = hdoc->pipe_fd[0];
	close(hdoc->pipe_fd[1]);
	free_heredoc(hdoc);
	return (EXIT_SUCCESS);
}

void	close_heredoc_fds(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == AST_REDIRECTION
		&& ast->u_data.redirection.direction == HEREDOC)
	{
		if (ast->u_data.redirection.heredoc_fd > 2)
		{
			close(ast->u_data.redirection.heredoc_fd);
			ast->u_data.redirection.heredoc_fd = -1;
		}
		close_heredoc_fds(ast->u_data.redirection.command);
	}
	else if (ast->type == AST_PIPELINE)
	{
		close_heredoc_fds(ast->u_data.pipeline.left);
		close_heredoc_fds(ast->u_data.pipeline.right);
	}
	else if (ast->type == AST_LOGICAL)
	{
		close_heredoc_fds(ast->u_data.logical.left);
		close_heredoc_fds(ast->u_data.logical.right);
	}
	else if (ast->type == AST_SUBSHELL)
		close_heredoc_fds(ast->u_data.subshell.child);
}
