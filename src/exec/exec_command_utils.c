/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/15 16:46:29 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*get_path_env(t_env_list *env)
{
	t_env_list	*path_node;

	path_node = find_env_node(env, "PATH");
	if (!path_node || !path_node->var_value)
	{
		ft_putstr_fd("minishell: PATH not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (path_node->var_value);
}

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

char	**convert_env_list_to_array(t_env_list *env_list)
{
	int			i;
	char		**envp;
	t_env_list	*current;

	i = 0;
	current = env_list->head;
	if (!env_list)
		return (NULL);
	while (current)
	{
		i++;
		current = current->next;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	current = env_list->head;
	while (current)
	{
		if (current->var_name && current->var_value)
		{
			char *temp = ft_strjoin(current->var_name, "=");
			if (!temp)
				return (NULL);
			envp[i] = ft_strjoin(temp, current->var_value);
			free(temp);
			if (!envp[i])
				return (NULL);
			i++;
		}
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}
