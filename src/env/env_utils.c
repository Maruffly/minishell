/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/27 09:47:28 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

void	update_env_node(t_env_list *list, char *var_name, char *var_value)
{
	t_env_list	*cur;

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
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
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
	new_node->head = NULL;
	list->head = new_node;
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
		if (!ft_isalpha(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env_list	*_env_token(char *name, t_env_list *env_tokens)
{
	t_env_list	*current;

	if (!name || !env_tokens)
		return (NULL);
	current = env_tokens->head;
	if (!name || !env_tokens)
		return (NULL);
	current = env_tokens->head;
	while (current)
	{
		if (current->var_name && ft_strcmp(current->var_name, name) == 0)
		if (current->var_name && ft_strcmp(current->var_name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}


