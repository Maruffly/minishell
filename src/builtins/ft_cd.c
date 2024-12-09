/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:10 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/09 13:47:27 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	exec_cd(t_command *cmd, t_env_list *env_list)
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
