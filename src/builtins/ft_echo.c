/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:36:17 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/11 18:44:33 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../includes/minishell.h"

void	exec_echo(t_command *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (cmd->right && !ft_strcmp(cmd->right->value, "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->right && cmd->right->next && cmd->right->next->value)
	{
		printf("%s", cmd->right->next->value);
		if (cmd->right->next->value)
			printf(" ");
		cmd->right = cmd->right->next;
	}
	if (!n_flag)
		printf("\n");
}
