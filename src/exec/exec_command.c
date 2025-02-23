/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/23 22:50:26 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

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

char	*find_command_path(char *command, t_env_list *env)
{
	char	*path;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path = search_in_path(command, env);
	return (path);
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
		if (sh->redirection_error)
			close(STDIN_FILENO);
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

void	extra_arguments(t_ast_command *cmd, t_shell *sh)
{
	char	*dup;
	t_token	*cur;

	if (sh->is_next_word && sh->extra_args)
	{
		cur = sh->extra_args;
		while (cur && is_word(cur))
		{
			if (cur->value)
			{
				dup = ft_strdup(cur->value);
				if (dup)
				{
					add_arg_tab(&cmd->args,remove_quotes(dup));
					/* free(dup); */
				}
			}
			cur = cur->next;
		}
		sh->is_next_word = false;
		sh->extra_args = NULL;
	}
}

int	exec_command(t_ast_command *cmd, t_exit end, t_shell *sh)
{
	int		status;
	extra_arguments(cmd, sh);
	status = EXIT_SUCCESS;
	sh->last_status = status;
	if (!cmd->args || !cmd->args[0])
		return (status);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_cd(cmd, sh->env, sh);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		exec_env(sh->env);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exec_exit(sh, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		exec_export(sh->env, cmd, sh);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		exec_unset(sh->env, cmd);
	else
		status = fork_command(cmd, end, sh);
	return (status);
}
