/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:35:04 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/30 15:56:35 by jmaruffy         ###   ########.fr       */
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
	hdoc->saved_stdout = 0;
	hdoc->bytes_read = 0;
	return (hdoc);
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

bool	process_heredoc_line(char *line, t_heredoc *hdoc, t_expand *exp, t_shell *sh)
{
	char	*expanded_line;

	expanded_line = handle_expansion(line, hdoc, sh, exp);
	if (!expanded_line)
		return (false);
	if (!write_to_pipe(hdoc->pipe_fd[1], expanded_line))
		return (false);
	free(expanded_line);
	return (true);
}
static int	heredoc_child(t_heredoc *hdoc, t_shell *sh, t_expand *exp)
{
	char	*line;

	(void)exp;
	close(hdoc->pipe_fd[0]);
	set_heredoc_signals();
	while (1)
	{
		sh->prompt_mode = HEREDOC_PROMPT;
		line = read_line(HEREDOC_PROMPT);
		if (!line)
		{
			if (g_signal_value == SIGINT)
			{
				close(hdoc->pipe_fd[1]);
				exit(130);
			}
			close(hdoc->pipe_fd[1]);
			return (heredoc_eof_handler(hdoc));
		}
		if (is_delimiter(line, hdoc->limiter))
		{
			free(line);
			close(hdoc->pipe_fd[1]);
			exit(EXIT_SUCCESS);
		}
		if (!process_heredoc_line(line, hdoc, exp, sh))
		{
			free(line);
			close(hdoc->pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
		/* free(line); */
	}
}

static int	heredoc_parent(pid_t child_pid)
{
	int	status;

	set_signal(SIGINT, SIG_IGN);
	set_signal(SIGQUIT, SIG_IGN);
	/* printf("Parent waiting for child process %d to finish...\n", child_pid); */
	waitpid(child_pid, &status, 0);
	set_main_signals();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		/* printf("Child process exited with status %d\n", WEXITSTATUS(status)); */
		return (131);
	}
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	return (EXIT_SUCCESS);
}

int	read_heredoc(t_heredoc *hdoc, t_shell *sh, t_expand *exp)
{
	int	status;

	hdoc->heredoc_pid = fork();
/* 	printf("PID_HEREDOC = %d\n", hdoc->heredoc_pid); */
	if (hdoc->heredoc_pid == -1)
	{
		perror("heredoc fork");
		return (EXIT_FAILURE);
	}
	if (hdoc->heredoc_pid == 0)
	{
		/* sleep(30); */
		status = heredoc_child(hdoc, sh, exp);
		exit(status);
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
	/* sh->prompt_mode = MAIN_PROMPT; */
	return (EXIT_SUCCESS);
}

int	handle_heredoc_ast(t_ast *ast, t_shell *sh)
{
	int			status;
	t_expand	exp;

	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_REDIRECTION && ast->u_data.redirection.direction == HEREDOC)
	{
		{
			ft_memset(&exp, 0, sizeof(t_expand));
			status = handle_heredoc(&ast->u_data.redirection, sh, &exp);
			if (status != EXIT_SUCCESS)
				return (status);
		}
		return (handle_heredoc_ast(ast->u_data.redirection.command, sh));
	}
	if (ast->type == AST_PIPELINE)
	{
		status = handle_heredoc_ast(ast->u_data.pipeline.left, sh);
		if (status != EXIT_SUCCESS)
			return (status);
		return (handle_heredoc_ast(ast->u_data.pipeline.right, sh));
	}
	if (ast->type == AST_LOGICAL)
	{
		status = handle_heredoc_ast(ast->u_data.logical.left, sh);
		if (status != EXIT_SUCCESS)
			return (status);
		return (handle_heredoc_ast(ast->u_data.logical.right, sh));
	}
	if (ast->type == AST_SUBSHELL)
		return (handle_heredoc_ast(ast->u_data.subshell.child, sh));
	return (EXIT_SUCCESS);
}
