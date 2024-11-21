/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:14:26 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/21 16:37:47 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

void	free_cmd_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			ft_free_split(cmd->args);
		if (cmd->command)
			free(cmd->command);
		free(cmd);
		cmd = tmp;
	}
}

void	free_env_list(t_env_list *list)
{
	t_env_node	*cur;
	t_env_node	*next;

	cur = list->head;
	while (cur)
	{
		next = cur->next;
		free_env_node(cur);
		cur = next;
	}
	free(list);
}

