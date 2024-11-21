/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/21 10:52:36 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/exec.h"

void	exec_builtin(t_command *cmd, t_env_list *env)
{
	if (strcmp(cmd->args[0], "cd") == 0)
		exec_cd(cmd, env);
	else if (strcmp(cmd->args[0], "echo") == 0)
		exec_echo(cmd);
	else if (strcmp(cmd->args[0], "pwd") == 0)
		exec_pwd(env);
	else if (strcmp(cmd->args[0], "export") == 0)
		exec_export(env, cmd);
	else if (strcmp(cmd->args[0], "unset") == 0)
		exec_unset(env, cmd);
	else if (strcmp(cmd->args[0], "env") == 0)
		exec_env(env);
	else if (strcmp(cmd->args[0], "exit") == 0)
		exec_exit(cmd);
	else
		ft_putstr_fd("Error: Command not recognized as builtin.\n", 2);
}

char	*get_path(char *cmd, char **envp)
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
		cmd_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(cmd_path, F_OK) == 0)
			return (ft_free_split(paths), cmd_path);
		free(cmd_path);
	}
	ft_free_split(paths);
	return (NULL);
}

void	exec_external(t_command *cmd, t_env_list *env)
{
	pid_t		pid;
	char	**envp;
	char	*path;

	envp = list_to_envp(env);
	pid = fork();
	path = get_path(cmd->args[0], envp);


	if (pid == 0)
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
		execve(path, cmd->args, envp);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}

void	execute_commands(t_command *cmd, t_env_list *env)
{
	t_command	*cur;
	int			is_builtin_flag;

	cur = cmd;
	while(cur)
	{
		is_builtin_flag = is_builtin(cur->args[0]);
		if (is_builtin_flag)
		{
			exec_builtin(cur, env);
		}
		else
		{
			exec_external(cur, env);
		}
		cur = cur->next;
	}
}

/* void	execute_builtin_with_redirection(t_command *cmd, t_env_list *env_list)
{

} */
