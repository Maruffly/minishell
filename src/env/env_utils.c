/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:13:16 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 15:36:55 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

void	update_env_node(t_env_list *list, char *var_name, char *var_value)
{
	t_env_node	*cur;

	cur = list->head;
	while (cur)
	{
		if (!ft_strcmp(cur->var_name, var_name))
		{
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

void	add_env_node(t_env_list *list, char *var_name, char *var_value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_node->var_name = ft_strdup(var_name);
	new_node->var_value = ft_strdup(var_value);
	if (!new_node->var_name || !new_node->var_value)
	{
		perror("strdup failed");
		exit(EXIT_FAILURE);
	}
	new_node->next = list->head;
	list->head = new_node;
}

void    remove_env_node(t_env_list *list, char *var_name)
{
	t_env_node  *cur;
	t_env_node  *prev;
	t_env_node  *next;

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
void	free_env_node(t_env_node *node)
{
	if (node)
	{
		free(node->var_name);
		free(node->var_value);
		free(node);
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
