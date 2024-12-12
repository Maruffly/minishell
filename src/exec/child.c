/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:08:45 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/12 12:48:19 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*get_path(t_ast_command *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	int		i;
	char	*part_path;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (ft_free_split(paths), NULL);
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(part_path, cmd->args[0]);
		free(part_path);
		if (access(cmd_path, F_OK) == 0)
			return (ft_free_split(paths), cmd_path);
		free(cmd_path);
	}
	ft_free_split(paths);
	return (NULL);
}

/* void	redir_command(t_command *cmd)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
}

void	close_unused_fds(t_command	*cmd)
{
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
}

void	setup_pipes(t_command *cmd)
{
	int	fd[2];

	if (cmd->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		cmd->output_fd = fd[1];
		cmd->next->input_fd = fd[0];
	}
	else
		cmd->output_fd = STDERR_FILENO;
}

int	update_prev_output_fd(t_command *cmd)
{
	if (cmd->next)
		return (cmd->next->input_fd);
	else
		return (STDIN_FILENO);
} */
