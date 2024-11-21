/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:13:16 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/21 10:53:07 by jmaruffy         ###   ########.fr       */
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

char	**list_to_envp(t_env_list *env)
{
	t_env_node	*cur;
	char		**envp;
	int			size;
	int			i;

	cur = env->head;
	size = 0;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
	{
		perror("malloc");
		return (NULL);
	}
	cur = env->head;
	i = 0;
	while (cur)
	{
		envp[i] = malloc(ft_strlen(cur->var_name) + ft_strlen(cur->var_value) + 2);
		if (!envp[i])
		{
			ft_free_split(envp);
			return (NULL);
		}
		ft_strcpy(envp[i], cur->var_name);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], cur->var_value);
		cur = cur->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
