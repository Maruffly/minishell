/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorislaine <jorislaine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:10 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/26 17:46:40 by jorislaine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

/*
void	exec_cd(t_ast_command *cmd, t_env_list *env_list)
{
	char		*path;
	char		*cur_pwd;
	t_env_list	*home_node;

	if (!cmd->args || !cmd->args[0])
	{
		ft_putstr_fd("cd: No command\n", 2);
		return;
	}
	cur_pwd = getcwd(NULL, 0);
	if (!cur_pwd)
	{
		perror("cd");
		return ;
	}
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("cd: Too many arguments\n", 2);
		free(cur_pwd);
		return;
	}
	if (!cmd->args[1])
	{
		home_node = find_env_node(env_list, "HOME");
		if (!home_node || !home_node->var_value)
		{
			ft_putstr_fd("cd: Home not set", 2);
			free(cur_pwd);
			return ;
		}
		path = home_node->var_value;
	}
	else
		path = cmd->args[1];
	if (access(path, F_OK) < 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		free(cur_pwd);
		return ;
	}
	if (chdir(path) < 0)
	{
		ft_putstr_fd("cd: Home not set", 2);
		perror(path);
		free(cur_pwd);
		return ;
	}
	update_pwd_env(env_list, cur_pwd);
	free(cur_pwd);
}
*/


void	update_pwd_env(t_env_list *env_list, char *old_pwd)
{
	char		*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("getcwd");
		return ;
	}
	if (old_pwd)
		update_env_node(env_list, "OLDPWD", old_pwd);
	update_env_node(env_list, "PWD", new_pwd);
	free(new_pwd);
}


static void handle_cd_error(char *path, char *cur_pwd)
{
	ft_putstr_fd("Omar&Fred: cd: ", 2);
	perror(path);
	free(cur_pwd);
}

static char *get_cd_path(t_ast_command *cmd, t_env_list *env_list)
{
	char *path;
	t_env_list *home_node;

	if (!cmd->args[1])
	{
		home_node = find_env_node(env_list, "HOME");
		if (!home_node || !home_node->var_value)
		{
			ft_putstr_fd("cd: Home not set", 2);
			return (NULL);
		}
		path = home_node->var_value;
	}
	else
		path = cmd->args[1];
	return (path);
}

static int change_directory(char *path, char *cur_pwd, t_env_list *env_list)
{
	if (access(path, F_OK) < 0)
	{
		handle_cd_error(path, cur_pwd);
		return (EXIT_FAILURE);
	}
	if (chdir(path) < 0)
    {
		handle_cd_error(path, cur_pwd);
		return (EXIT_FAILURE);
	}
	update_pwd_env(env_list, cur_pwd);
	free(cur_pwd);
	return (EXIT_SUCCESS);
}

void exec_cd(t_ast_command *cmd, t_env_list *env_list)
{
    char *path;
    char *cur_pwd;

    if (!cmd->args || !cmd->args[0])
    {
        ft_putstr_fd("cd: No command\n", 2);
        return;
    }
    cur_pwd = getcwd(NULL, 0);
    if (!cur_pwd)
    {
        perror("cd");
        return;
    }
    if (cmd->args[2] != NULL)
    {
        ft_putstr_fd("cd: Too many arguments\n", 2);
        free(cur_pwd);
        return;
    }
    path = get_cd_path(cmd, env_list);
    if (!path)
    {
        free(cur_pwd);
        return;
    }
    change_directory(path, cur_pwd, env_list);
}
