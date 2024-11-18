/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:28:47 by jbmy              #+#    #+#             */
/*   Updated: 2024/11/18 18:42:23 by jbmy             ###   ########.fr       */
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
		/* else
		{
			exec_external(cur, env);
		} */
		cur = cur->next;
	}
}

/* void	execute_builtin_with_redirection(t_command *cmd, t_env_list *env_list)
{

} */