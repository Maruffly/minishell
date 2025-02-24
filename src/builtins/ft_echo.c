/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:36:17 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/24 17:34:57 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	exec_echo(t_ast_command *cmd)
// {
// 	int	i;
// 	int	n_flag;

// 	i = 1;
// 	n_flag = 0;
// 	while (cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
// 	{
// 		n_flag = 1;
// 		i++;
// 	}
// 	while (cmd->args[i])
// 	{
// 		if (ft_strcmp(cmd->args[i], "-n"))
// 		{
// 			printf("%s", cmd->args[i]);
// 			if (cmd->args[i + 1] && ft_strcmp(cmd->args[i + 1], "-n"))
// 				printf(" ");
// 		}
// 		i++;
// 	}
// 	if (!n_flag)
// 		printf("\n");
// }

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
	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[i], "-n"))
		{
			if (write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i])) == -1)
				return ; // 🔹 Si le pipe est fermé, on arrête l'écriture
			if (cmd->args[i + 1] && ft_strcmp(cmd->args[i + 1], "-n"))
			{
				if (write(STDOUT_FILENO, " ", 1) == -1)
					return ;
			}
		}
		i++;
	}
	if (!n_flag)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return ;
	}
}
