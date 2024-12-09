/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/09 13:48:09 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	exec_builtin(t_command *cmd, t_env_list *env)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_cd(cmd, env);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		exec_export(env, cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		exec_unset(env, cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		exec_env(env);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exec_exit(cmd);
	else
		ft_putstr_fd("Error: Command not recognized as builtin.\n", 2);
}

void	exec_external(t_command *cmd, t_env_list *env)
{
	pid_t		pid;
	char		**envp;
	char		*path;

	envp = list_to_envp(env);
	path = get_path(cmd->command, envp);
	/*check if path exist*/
	pid = fork();
	if (pid == 0)
	{
		redir_command(cmd);
		if (execve(path, cmd->args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
	free(path);
}

void	execute_command(t_command *cmd, t_env_list *env, int prev_output_fd)
{
	if (!cmd)
		return ;
	cmd->input_fd = prev_output_fd;
	/* int i;
	for (i = 0; cmd->args[i]; i++)
		printf("%s\n", cmd->args[i]); */
	if (is_builtin(cmd->command))
		exec_builtin(cmd, env);
	else
		exec_external(cmd, env);
}

void	execute_pipeline(t_command *cmd, t_env_list *env)
{
	t_command	*cur;
	int			prev_output_fd;

	prev_output_fd = STDIN_FILENO;
	cur = cmd;
	while (cur)
	{
		if (!cur->command) // Vérification supplémentaire
		{
			ft_putstr_fd("Error: Null command in pipeline.\n", 2);
			cur = cur->next;
			continue;
		}
		setup_pipes(cmd);
		execute_command(cur, env, prev_output_fd);
		close_unused_fds(cur);
		prev_output_fd = update_prev_output_fd(cur);
		cur = cur->next;
	}
}
