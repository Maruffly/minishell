/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:21:14 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 16:04:42 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"

void	exec_exit(t_env_list *env_list, t_command *cmd)
{
	int	exit_status;
	(void)env_list;
	if (!cmd->right)
	{
		printf("exit\n");
		exit(0);
	}
	if (cmd->right->next)
	{
		ft_putstr_fd("exit: numeric args only\n", 2);
		exit(255);
	}
	exit_status = ft_atoi(cmd->right->value);
	printf("exit\n");
	exit(exit_status);
}
