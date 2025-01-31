/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:35:04 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/31 18:24:13 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_delimiter(char *line, char *delimiter)
{
	return (ft_strcmp(line, delimiter) == 0);
}

static int	heredoc_parent(pid_t child_pid)
{
	int	status;

	set_signal(SIGINT, SIG_IGN);
	set_signal(SIGQUIT, SIG_IGN);
	waitpid(child_pid, &status, 0);
	set_main_signals();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		return (131);
	}
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	return (EXIT_SUCCESS);
}

static int	heredoc_child(t_heredoc *hdoc, t_shell *sh, t_expand *exp)
{
	char	*line;

	close(hdoc->pipe_fd[0]);
	set_heredoc_signals();
	while (1)
	{
		sh->prompt_mode = HEREDOC_PROMPT;
		line = read_line(HEREDOC_PROMPT);
		if (!line)
			heredoc_signal_exit(hdoc);
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
	}
}

int	read_heredoc(t_heredoc *hdoc, t_shell *sh, t_expand *exp)
{
	int	status;

	hdoc->heredoc_pid = fork();
	if (hdoc->heredoc_pid == -1)
	{
		perror("heredoc fork");
		return (EXIT_FAILURE);
	}
	if (hdoc->heredoc_pid == 0)
	{
		status = heredoc_child(hdoc, sh, exp);
		exit(status);
	}
	return (heredoc_parent(hdoc->heredoc_pid));
}
