/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:28:12 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 16:50:38 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"

void	exec_unset(t_env_list *env_list, t_command *cmd)
{
	char	**args;
	int		i;

	if (!cmd->right)
		return ;
	args = ft_split(cmd->right->value, ' ');
	i = 0;
	while (args[i])
	{
		remove_env_node(env_list, args[i]);
		i++;
	}
	ft_free_split(args);
}
