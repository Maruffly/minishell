/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:10 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/19 16:16:47 by jlaine           ###   ########.fr       */
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

static char	*get_cd_path(t_ast_command *cmd, t_env_list *env_list, t_shell *sh)
{
	t_env_list	*home_node;
	char		*path;

	path = NULL;
	if (!cmd->args[1])
	{
		home_node = find_env_node(env_list, "HOME");
		if (!home_node || !home_node->var_value)
		{
			ft_putstr_fd("cd: Home not set\n", STDERR_FILENO);
			sh->last_status = 1;
			return (NULL);
		}
		path = home_node->var_value;
	}
	else if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("Omar&Fred: cd: too many arguments\n", STDERR_FILENO);
		sh->last_status = 1;
		return (NULL);
	}
	else
		path = cmd->args[1];
	return (path);
}

static int	change_directory(char *path, char *cur_pwd,
							t_env_list *env_list, t_shell *sh)
{
	int	access_result;
	int	chdir_result;

	access_result = access(path, F_OK);
	chdir_result = chdir(path);
	if (access_result < 0 || chdir_result < 0)
	{
		ft_putstr_fd("Omar&Fred: cd: ", STDERR_FILENO);
		perror(path);
		free(cur_pwd);
		sh->last_status = 1;
		return (EXIT_FAILURE);
	}
	update_pwd_env(env_list, cur_pwd);
	free(cur_pwd);
	sh->last_status = 0;
	return (EXIT_SUCCESS);
}

static int	check_cd_args(t_ast_command *cmd, char **cur_pwd, t_shell *sh)
{
	*cur_pwd = NULL;
	if (!cmd->args || !cmd->args[0])
	{
		ft_putstr_fd("Omar&Fred: cd: No command\n", STDERR_FILENO);
		sh->last_status = 1;
		return (EXIT_FAILURE);
	}
	*cur_pwd = getcwd(NULL, 0);
	if (!*cur_pwd)
	{
		perror("cd");
		sh->last_status = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	exec_cd(t_ast_command *cmd, t_env_list *env_list, t_shell *sh)
{
	char	*cur_pwd;
	char	*path;

	if (check_cd_args(cmd, &cur_pwd, sh) == EXIT_FAILURE)
		return ;
	path = get_cd_path(cmd, env_list, sh);
	if (!path)
	{
		free(cur_pwd);
		return ;
	}
	change_directory(path, cur_pwd, env_list, sh);
}
