/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sorting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:15:56 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/11 14:41:54 by jlaine           ###   ########.fr       */
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

static void	add_exported_var(t_env_list *list, char *var_name)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		handle_malloc_error();
	new_node->var_name = ft_strdup(var_name);
	handle_strdup_error(new_node->var_name);
	new_node->var_value = NULL;
	new_node->next = list->head;
	list->head = new_node;
}

void	add_or_update_env(t_env_list *list, char *var_name, char *var_value)
{
	t_env_list	*current;

	if (!list || !var_name)
		return ;
	current = list->head;
	while (current)
	{
		if (ft_strcmp(current->var_name, var_name) == 0)
		{
			free(current->var_value);
			if (var_value)
				current->var_value = ft_strdup(var_value);
			else
				current->var_value = NULL;
			return ;
		}
		current = current->next;
	}
	if (!var_value)
	{
		add_exported_var(list, var_name);
		return ;
	}
	add_env_node(list, var_name, var_value);
}
