/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:28:12 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 17:17:15 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"

void	exec_unset(t_env_list *env_list, t_command *cmd)
{
	char	**args;
	int		i;

	if (!cmd->right || !cmd->right->value)
		return ;
	args = ft_split(cmd->right->value, ' ');
	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (find_env_node(env_list, args[i]))
			remove_env_node(env_list, args[i]);
		else
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		}
		i++;
	}
	ft_free_split(args);
}
