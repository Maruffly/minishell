/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:36:17 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 09:56:13 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	option_check(char **args, int *i, char c)
{
	int		j;
	bool	detected;

	detected = false;
	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] == c)
			j++;
		if (args[*i][j - 1] == c && args[*i][j] == '\0')
			detected = true;
		else
			return (detected);
		(*i)++;
	}
	return (detected);
}

int	exec_echo(t_ast_command *cmd, t_shell *sh)
{
	bool	new_line;
	int		i;

	i = 1;
	new_line = !(option_check(cmd->args, &i, 'n'));
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
