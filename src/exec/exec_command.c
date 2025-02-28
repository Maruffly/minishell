/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:47:42 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:09:45 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_builtin_func	get_builtin_function(char *cmd_name)
{
	int				i;
	const t_builtin	builtins[] = {{"echo", exec_echo}, {"cd", exec_cd},
	{"pwd", exec_pwd}, {"export", exec_export}, {"unset",
		exec_unset}, {"env", exec_env}, {"exit", exec_exit}, {NULL,
		NULL}};

	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(cmd_name, builtins[i].name) == 0)
			return (builtins[i].func);
		i++;
	}
	return (NULL);
}

int	fork_command(t_ast_command *cmd, t_execute_end end, t_shell *sh)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (end == O_EXIT)
		execve_s(get_bin_path(cmd->args[0], sh), cmd->args,
			env_to_char_array(sh), sh);
	else
	{
		pid = fork_s(sh);
		if (pid == 0)
		{
			sh->in_main_process = false;
			set_signal_child_process();
			execve_s(get_bin_path(cmd->args[0], sh), cmd->args,
				env_to_char_array(sh), sh);
		}
		wait_s(&status, sh);
		status = check_process_child_exit(status, NULL, sh);
	}
	return (status);
}

int	exec_cmd(t_ast_command *cmd, t_execute_end end, t_shell *sh)
{
	int				status;
	t_builtin_func	builtin;

	status = EXIT_SUCCESS;
	if (cmd->args[0] == NULL)
		return (status);
	builtin = get_builtin_function(cmd->args[0]);
	if (builtin)
		return (builtin(cmd, sh));
	else
		status = fork_command(cmd, end, sh);
	return (status);
}
