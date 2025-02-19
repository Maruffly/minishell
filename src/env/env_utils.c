/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/19 15:35:36 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_node(t_env_list *list, char *var_name, char *var_value)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		handle_malloc_error();
	new_node->var_name = ft_strdup(var_name);
	if (!new_node->var_name)
	{
		free(new_node);
		handle_strdup_error(NULL);
	}
	if (var_value)
		new_node->var_value = ft_strdup(var_value);
	else
		new_node->var_value = ft_strdup("");
	if (!new_node->var_name)
	{
		free(new_node->var_name);
		free(new_node);
		handle_strdup_error(new_node->var_value);
	}
	new_node->next = list->head;
	new_node->head = NULL;
	list->head = new_node;
}

void	update_env_node(t_env_list *list, char *var_name, char *var_value)
{
	t_env_list	*cur;

	cur = list->head;
	while (cur)
	{
		if (!ft_strcmp(cur->var_name, var_name))
		{
			if (cur->var_value)
				free(cur->var_value);
			cur->var_value = ft_strdup(var_value);
			if (!cur->var_value)
			{
				perror("strdup failed");
				exit(EXIT_FAILURE);
			}
			return ;
		}
		cur = cur->next;
	}
	add_env_node(list, var_name, var_value);
}

void	remove_env_node(t_env_list *list, char *var_name)
{
	t_env_list	*cur;
	t_env_list	*prev;
	t_env_list	*next;

	cur = list->head;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->var_name, var_name))
		{
			next = cur->next;
			if (prev)
				prev->next = next;
			else
				list->head = next;
			free(cur->var_name);
			free(cur->var_value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	is_valid_var_name(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env_list	*find_env_node(t_env_list *list, char *name)
{
	t_env_list	*cur;

	cur = list->head;
	while (cur)
	{
		if (ft_strcmp(cur->var_name, name) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
