/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/15 14:19:23 by jlaine           ###   ########.fr       */
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

	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	if (!path)
		return (NULL);
	path = ft_strjoin(path, command);
	if (!path)
		return (NULL);
	if (!path)
		return (NULL);
	return (path);
}

char	**convert_env_list_to_array(t_env_list *env_list)
{
	int			i;
	char		**envp;
	t_env_list	*current;
	
	i = 0;
	current = env_list;
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
	current = env_list;
	printf("var name %s\n", current->var_name);
	while (current)
	{
		envp[i] = ft_strjoin(current->var_name, "="); // segfault - var_name == NULL
		envp[i] = ft_strjoin(envp[i], current->var_value);
		i++;
		current = current->next;
	}
	return (envp);
}
