/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:28:12 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/18 16:02:05 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"

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
