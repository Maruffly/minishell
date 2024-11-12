/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:10 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 16:49:15 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"

void	exec_cd(t_command *cmd, t_env_list *env_list)
{
	char		*path;
	t_env_node	*home_node;

	if (!cmd->right || !cmd->right->value)
	{
		home_node = find_env_node(env_list, "HOME");
		if (!home_node || !home_node->var_value)
		{
			ft_putstr_fd("cd: Home not set", 2);
			return ;
		}
		path = home_node->var_value;
	}
	else
		path = cmd->right->value;
	if (chdir(path) == -1)
		perror("cd");
	else
		update_pwd_env(env_list);
}

void	update_pwd_env(t_env_list	*env_list)
{
	char		*pwd;
	t_env_node	*pwd_node;
	t_env_node	*oldpwd_node;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		return ;
	}
	pwd_node = find_env_node(env_list, "PWD");
	oldpwd_node = find_env_node(env_list, "OLDPWD");
	if (pwd_node && pwd_node->var_value)
	{
		if (oldpwd_node)
			update_env_node(env_list, "OLDPWD", oldpwd_node->var_value);
		else
			add_env_node(env_list, "OLDPWD", pwd_node->var_value);
	}
	if (pwd_node)
		update_env_node(env_list, "PWD", pwd);
	else
		add_env_node(env_list, "PWD", pwd);
	free(pwd);
}
