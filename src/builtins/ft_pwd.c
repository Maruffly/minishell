/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:18:25 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 20:28:50 by jmaruffy         ###   ########.fr       */
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
		s_alloc(getcwd_ret, PROMPT, sh);
		write_s(getcwd_ret, STDOUT_FILENO, sh);
		write_s("\n", STDOUT_FILENO, sh);
		return (0);
	}
	write_s(current_directory, STDOUT_FILENO, sh);
	write_s("\n", STDOUT_FILENO, sh);
	return (0);
}
