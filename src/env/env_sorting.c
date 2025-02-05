/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sorting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:15:56 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/05 11:25:14 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	insert_sorted_node(t_env_list **sorted, t_env_list *node)
{
	t_env_list	*tmp;

	if (!*sorted || ft_strcmp(node->var_name, (*sorted)->var_name) < 0)
	{
		node->next = *sorted;
		*sorted = node;
		return ;
	}
	tmp = *sorted;
	while (tmp->next && ft_strcmp(node->var_name, tmp->next->var_name) >= 0)
		tmp = tmp->next;
	node->next = tmp->next;
	tmp->next = node;
}

void	sort_env_list(t_env_list *list)
{
	t_env_list	*sorted;
	t_env_list	*cur;
	t_env_list	*next;

	if (!list || !list->head)
		return ;
	sorted = NULL;
	cur = list->head;
	while (cur)
	{
		next = cur->next;
		insert_sorted_node(&sorted, cur);
		cur = next;
	}
	list->head = sorted;
}
