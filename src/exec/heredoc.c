/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:35:04 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/20 16:02:10 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void free_heredoc(t_heredoc *hdoc)
{
	if (!hdoc)
		return ;
	free(hdoc->limiter);
	free(hdoc);
}

t_heredoc	*init_heredoc(char *delimiter)
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
	return (hdoc);
}

int	read_heredoc(t_heredoc *hdoc, t_shell *sh)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
			return (heredoc_eof_handler(hdoc));
		if (ft_strcmp(line, hdoc->limiter) == 0)
		{
			free(line);
			break ;
		}
		if (hdoc->expand_vars)
		{
			if (expand_vars(&line, sh) != EXIT_SUCCESS)
			{
				free(line);
				return (EXIT_FAILURE);
			}
		}
		write(hdoc->pipe_fd[1], line, ft_strlen(line));
		write(hdoc->pipe_fd[1], "\n", 1);
		free(line);
	}
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_ast_redirection *redir, t_shell *sh)
{
	t_heredoc	*hdoc;

	hdoc = init_heredoc(redir->file);
	if (!hdoc)
		return (EXIT_FAILURE);
	if (pipe(hdoc->pipe_fd) == -1)
	{
		free_heredoc(hdoc);
		return (perror("heredoc pipe"), EXIT_FAILURE);
	}
	if (read_heredoc(hdoc, sh) != EXIT_SUCCESS)
	{
		free_heredoc(hdoc);
		return (EXIT_FAILURE);
	}
	redir->heredoc_fd = hdoc->pipe_fd[0];
	close(hdoc->pipe_fd[1]);
	free_heredoc(hdoc);
	return (EXIT_SUCCESS);
}

int	execute_heredoc(t_ast *ast, t_shell *sh)
{
	int	status;

	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_REDIRECTION)
	{
		if (ast->u_data.redirection.direction == HEREDOC)
		{
			status = handle_heredoc(&ast->u_data.redirection, sh);
			if (!status)
				return (status);
		}
		return (execute_heredoc(ast->u_data.redirection.command, sh));
	}
	if (ast->type == AST_PIPELINE)
	{
		status = execute_heredoc(ast->u_data.pipeline.left, sh);
		if (status != EXIT_SUCCESS)
			return (status);
		return (execute_heredoc(ast->u_data.pipeline.right, sh));
	}
	if (ast->type == AST_LOGICAL)
	{
		status = execute_heredoc(ast->u_data.logical.left, sh);
		if (status != EXIT_SUCCESS)
			return (status);
		return (execute_heredoc(ast->u_data.logical.right, sh));
	}
	if (ast->type == AST_SUBSHELL)
		return (execute_heredoc(ast->u_data.subshell.child, sh));
	return (EXIT_SUCCESS);
}
