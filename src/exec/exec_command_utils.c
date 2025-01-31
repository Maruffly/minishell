/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:19:04 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/31 16:27:39 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_path(char *dir, char *command)
{
	char	*path;
	char	*temp;

	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	temp = ft_strjoin(path, command);
	free(path);
	if (!temp)
		return (NULL);
	return (temp);
}

static int	env_list_size(t_env_list *env_list)
{
	t_env_list	*current;
	int			count;

	if (!env_list)
		return (0);
	current = env_list->head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	*build_env_pair(t_env_list *node)
{
	char	*temp;
	char	*env_string;

	temp = ft_strjoin(node->var_name, "=");
	if (!temp)
		return (NULL);
	env_string = ft_strjoin(temp, node->var_value);
	free(temp);
	return (env_string);
}

static int	fill_env_array(char **envp, t_env_list *env_list)
{
	t_env_list	*current;
	int			i;

	current = env_list->head;
	i = 0;
	while (current)
	{
		if (current->var_name && current->var_value)
		{
			envp[i] = build_env_pair(current);
			if (!envp[i])
				return (EXIT_FAILURE);
			i++;
		}
		current = current->next;
	}
	envp[i] = NULL;
	return (EXIT_SUCCESS);
}

char	**convert_env_list_to_array(t_env_list *env_list)
{
	char	**envp;
	int		size;

	size = env_list_size(env_list);
	envp = ft_calloc(size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	if (fill_env_array(envp, env_list) == EXIT_FAILURE)
	{
		ft_free_split(envp);
		return (NULL);
	}
	return (envp);
}
