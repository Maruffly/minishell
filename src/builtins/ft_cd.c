/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:10 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/18 13:59:24 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_env(t_env_list *env_list, char *old_pwd)
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

static char	*get_cd_path(t_ast_command *cmd, t_env_list *env_list)
{
	t_env_list	*home_node;

	if (!cmd->args[1])
	{
		home_node = find_env_node(env_list, "HOME");
		if (!home_node || !home_node->var_value)
		{
			ft_putstr_fd("cd: Home not set\n", 2);
			return (NULL);
		}
		return (home_node->var_value);
	}
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("Omar&Fred: cd: Too many arguments\n", 2);
		return (NULL);
	}
	return (cmd->args[1]);
}

static int	change_directory(char *path, char *cur_pwd, t_env_list *env_list)
{
	if (access(path, F_OK) < 0 || chdir(path) < 0)
	{
		ft_putstr_fd("Omar&Fred: cd: ", 2);
		perror(path);
		free(cur_pwd);
		return (EXIT_FAILURE);
	}
	update_pwd_env(env_list, cur_pwd);
	free(cur_pwd);
	return (EXIT_SUCCESS);
}

static int	check_cd_args(t_ast_command *cmd, char **cur_pwd)
{
	if (!cmd->args || !cmd->args[0])
	{
		ft_putstr_fd("Omar&Fred: cd: No command\n", 2);
		return (EXIT_FAILURE);
	}
	*cur_pwd = getcwd(NULL, 0);
	if (!*cur_pwd)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	exec_cd(t_ast_command *cmd, t_env_list *env_list)
{
	char	*cur_pwd;
	char	*path;

	if (check_cd_args(cmd, &cur_pwd) == EXIT_FAILURE)
		return ;
	path = get_cd_path(cmd, env_list);
	if (!path)
	{
		free(cur_pwd);
		return ;
	}
	change_directory(path, cur_pwd, env_list);
}
