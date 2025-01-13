/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:35:04 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/13 14:08:50 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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

static bool	is_delimiter(char *line, char *delimiter)
{
	return (ft_strcmp(line, delimiter) == 0);
}

static char	*handle_expansion(char *line, t_heredoc *hdoc, t_shell *sh, t_expand *exp)
{
	char	*expand_line;

	if (!hdoc->expand_vars)
		return (line);
	expand_line = expand_heredoc_vars(line, sh, exp);
	free(line);
	if (!expand_line)
	{
		printf("Exp failure");
		return (NULL);
	}
	return (expand_line);	
}

static bool	write_to_pipe(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1
		|| write(fd, "\n", 1) == -1)
		return (false);
	return (true);
}

static int	heredoc_child(t_heredoc *hdoc, t_shell *sh, t_expand *exp)
{
	char	*line;
	char	*proc_line;

	close(hdoc->pipe_fd[0]);
	set_heredoc_signals();
	while (1)
	{
		line = read_line(HEREDOC_PROMPT);
		if (!line)
		{
			printf("!line\n");
			return (heredoc_eof_handler(hdoc));
		}
		if (is_delimiter(line, hdoc->limiter))
			return (free(line), EXIT_SUCCESS);
		proc_line = handle_expansion(line, hdoc, sh, exp);
		if (!proc_line)
			return (EXIT_FAILURE);
		if (!write_to_pipe(hdoc->pipe_fd[1], proc_line))
			return (free(line), EXIT_FAILURE);
		free(proc_line);
	}
}

static int	heredoc_parent(pid_t child_pid)
{
	int	status;

	waitpid(child_pid, &status, 0);
	if (WIFSIGNALED(status))
		return (130);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

int	read_heredoc(t_heredoc *hdoc, t_shell *sh, t_expand *exp)
{
	hdoc->heredoc_pid = fork();
	printf("PID_HEREDOC = %d\n", hdoc->heredoc_pid);
	if (hdoc->heredoc_pid == -1)
	{
		perror("heredoc fork");
		return (EXIT_FAILURE);
	}
	if (hdoc->heredoc_pid == 0)
	{
		sleep(10);
		exit(heredoc_child(hdoc, sh, exp));
	}
	return (heredoc_parent(hdoc->heredoc_pid));
}

int	handle_heredoc(t_ast_redirection *redir, t_shell *sh, t_expand *exp)
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
	sh->prompt_mode = MAIN_PROMPT;
	return (EXIT_SUCCESS);
}

int	execute_heredoc(t_ast *ast, t_shell *sh)
{
	int			status;
	t_expand	exp;
	
	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_REDIRECTION)
	{
		if (ast->u_data.redirection.direction == HEREDOC)
		{
			memset(&exp, 0, sizeof(t_expand));
			status = handle_heredoc(&ast->u_data.redirection, sh, &exp);
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
