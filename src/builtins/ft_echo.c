/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:36:17 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/24 18:16:09 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo_args(char **args, int i)
{
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n"))
		{
			if (write(STDOUT_FILENO, args[i], ft_strlen(args[i])) == -1)
				return ;
			if (args[i + 1] && ft_strcmp(args[i + 1], "-n"))
			{
				if (write(STDOUT_FILENO, " ", 1) == -1)
					return ;
			}
		}
		i++;
	}
}

void	exec_echo(t_ast_command *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
	{
		n_flag = 1;
		i++;
	}
	print_echo_args(cmd->args, i);
	if (!n_flag)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return ;
	}
}
