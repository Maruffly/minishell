/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:10 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/11 15:38:16 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../includes/minishell.h"

void	exec_cd(t_command *cmd, t_env_list *env_list)
{
	char	*path;

	if (!cmd->right || !cmd->right->value)
	{
		path = getenv("HOME");
		if (!path)
			ft_putstr_fd("cd: Home not set", 2);
	}
	else
		path = cmd->right->value;
	if (chdir(path) == -1)
		perror("path does not exist");
	else
		update_pwd_env(env_list);
}

void	update_pwd_env(t_env_list	*env_list)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		return ;
	}
	oldpwd = getenv("PWD");
	if (oldpwd)
		update_env_var(env_list, "OLDPWD", oldpwd);
	update_env_var(env_list, "PWD", pwd);
	free(pwd);
}
