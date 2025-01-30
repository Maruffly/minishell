/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:19:04 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/30 16:47:24 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static char	*search_in_path(char *command, t_env_list *env)
{
	int		i;
	char	*path;
	char	*path_env;
	char	**paths;

	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = build_path(paths[i], command);
		if (access(path, F_OK) == 0)
		{
			ft_free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

static char	*find_command_path(char *command, t_env_list *env)
{
	char	*path;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path = search_in_path(command, env);
	return (path);
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
	if (access(path, X_OK) < 0)
	{
		ft_putstr_fd("Omar&Fred: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": permission denied\n", STDERR_FILENO);
		exit(126);
	}
	envp = convert_env_list_to_array(sh->env);
	execve(path, cmd->args, envp);
	perror("execve");
	free(path);
	free_env_array(envp);
	exit(EXIT_FAILURE);
}

static int	fork_command(t_ast_command *cmd, t_exit end, t_shell *sh)
{
	pid_t	pid;
	int		status;

	(void)end;
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		sh->is_parent = false;
		set_child_signals();
		exec_extern_command(cmd, sh);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(&status);
		sh->last_status = check_process_child_exit(status, NULL, sh);
	}
	else
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	return (sh->last_status);
}

int	exec_command(t_ast_command *cmd, t_exit end, t_shell *sh)
{
	int	status;

	status = EXIT_SUCCESS;
	if (!cmd->args || !cmd->args[0])
		return (status);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_cd(cmd, sh->env);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		exec_env(sh->env);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exec_exit(sh, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		exec_export(sh->env, cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		exec_unset(sh->env, cmd);
	else
		status = fork_command(cmd, end, sh);
	sh->last_status = status;
	return (status);
}
