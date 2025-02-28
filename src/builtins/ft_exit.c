/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:21:14 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 19:46:48 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_valid_numeric_argument(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (false);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (false);
	while (arg[i])
	{
		if (!ft_isdigit((unsigned char)arg[i]))
			return (false);
		i++;
	}
	return (true);
}

int	exec_exit(t_ast_command *cmd, t_shell *sh)
{
	long	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!cmd->args[1])
		exit_shell(sh->last_status, sh);
	if (!is_valid_numeric_argument(cmd->args[1]))
	{
		ft_putstr_fd("Omar&Fred: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_shell(2, sh);
	}
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("Omar&Fred: exit: too many arguments\n", STDERR_FILENO);
		sh->last_status = 1;
		return (EXIT_FAILURE);
	}
	exit_code = ft_atoi(cmd->args[1]);
	exit_shell((unsigned char)exit_code, sh);
	return (EXIT_SUCCESS);
}
