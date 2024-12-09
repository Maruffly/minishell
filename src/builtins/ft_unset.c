/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:28:12 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/09 13:47:53 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	exec_unset(t_env_list *env_list, t_command *cmd)
{
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_var_name(cmd->args[i]))
			remove_env_node(env_list, cmd->args[i]);
		else
			ft_putstr_fd("unset: invalid identifier\n", STDERR_FILENO);
		i++;
	}
}
