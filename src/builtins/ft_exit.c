/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:21:14 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/19 16:17:12 by jlaine           ###   ########.fr       */
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

bool	not_numeric_args(char **args, t_shell *sh)
{
	if (!args[1])
		return (false);
	if (!is_valid_numeric_argument(args[1]))
	{
		ft_putstr_fd("Omar&Fred: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		sh->last_status = 2;
		sh->must_exit = true;
		return (true);
	}
	return (false);
}

void	exec_exit(t_shell *sh, t_ast_command *cmd)
{
	bool	not_num_arg;
	long	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!cmd->args[1])
	{
		sh->must_exit = true;
		return ;
	}
	not_num_arg = not_numeric_args(cmd->args, sh);
	if (not_num_arg)
		return ;
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("Omar&Fred: exit: too many arguments\n", STDERR_FILENO);
		sh->last_status = 1;
		return ;
	}
	exit_code = ft_atoi(cmd->args[1]);
	sh->last_status = (unsigned char)exit_code;
	sh->must_exit = true;
}

void	free_heredoc(t_heredoc *hdoc)
{
	if (!hdoc)
		return ;
	free(hdoc->limiter);
	free(hdoc);
}
