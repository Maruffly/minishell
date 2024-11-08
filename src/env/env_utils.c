/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:13:16 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/08 17:29:24 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../includes/minishell.h"

t_env_list	*init_env_list(void)
{
	t_env_list	*list;

	list = malloc(sizeof(t_env_list));
	if (!list)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	return (list);
}

void	update_env_var(t_env_list *list, char *var_name, char *var_value)
{
	t_env_node	*cur;
	t_env_node	*prev;

	cur = list->head;
	prev = NULL;
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
		prev = cur;
		cur = cur->next;
	}
}

void	add_env_var(t_env_list *list, char *var_name, char *var_value, t_env_node *prev)
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
	new_node->next = NULL;
	if (!new_node->var_name || !new_node->var_value)
	{
		perror("strdup failed");
		exit(EXIT_FAILURE);
	}
	if (prev)
		prev->next = new_node;
	else
		list->head = new_node;
}

void	remove_env_var(t_env_list *list, char *var_name, char *var_value)
{
	t_env_node	*cur;
	t_env_node	*prev;

	cur = list->head;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->var_name, var_name) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				list->head = cur->next;
		}
		free(cur->var_name);
		free(cur->var_value);
		free(cur);
		return ;
	}
	prev = cur;
	cur = cur->next;
}

void	free_env_list(t_env_list	*list)
{
	t_env_node	*cur;
	t_env_node	*tmp;

	cur = list->head;
	while (cur)
	{
		tmp = cur;
		free(tmp->var_name);
		free(tmp->var_name);
		free(tmp);
	}
	free(list);
}

void	print_env_list(t_env_list	*list)
{
	t_env_node	*cur;

	cur = list->head;
	while (cur)
	{
		printf("%s=%s", cur->var_name, cur->var_value);
		cur = cur->next;
	}
}
