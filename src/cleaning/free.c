/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:18:42 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 12:27:58 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_var(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	free(var->name);
	free(var->value);
	free(var);
}

void	remove_list_node(t_list **node, t_list **head,
	void (*free_function)(void *), bool free_node)
{
	t_list	*to_remove;

	if (!node || !*node)
		return ;
	to_remove = *node;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	else
		*head = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	if (free_node)
		ft_lstdelone(to_remove, free_function);
}
