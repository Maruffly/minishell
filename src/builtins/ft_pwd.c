/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:18:25 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 09:56:31 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_pwd(t_ast_command *cmd, t_shell *sh)
{
	char	*current_directory;
	char	*getcwd_ret;

	(void)cmd;
	current_directory = value(env_var("PWD", sh->env));
	if (!current_directory)
	{
		getcwd_ret = getcwd(NULL, 0);
		if (!getcwd_ret)
			return (error_handler("getcwd", errno, sh), 1);
		safe_alloc(getcwd_ret, PROMPT, sh);
		ft_putstr_fd(getcwd_ret, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	ft_putstr_fd(current_directory, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
