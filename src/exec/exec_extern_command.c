/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:47:42 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/14 17:50:52 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_if_directory(char *path, char *cmd)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("Omar&Fred: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		free(path);
		exit(126);
	}
}

static void	check_executable_access(char *path, char *cmd)
{
	if (access(path, X_OK) < 0)
	{
		ft_putstr_fd("Omar&Fred: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": permission denied\n", STDERR_FILENO);
		free(path);
		exit(126);
	}
}

void	exec_extern_command(t_ast_command *cmd, t_shell *sh)
{
	char	*path;
	char	**envp;

	path = find_command_path(cmd->args[0], sh->env);
	if (!path)
	{
		ft_putstr_fd("Omar&Fred: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	check_if_directory(path, cmd->args[0]);
	check_executable_access(path, cmd->args[0]);
	envp = convert_env_list_to_array(sh->env);
	execve(path, cmd->args, envp);
	perror("execve");
	free(path);
	free_env_array(envp);
	exit(EXIT_FAILURE);
}
