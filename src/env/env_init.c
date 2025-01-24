/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/24 16:46:31 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

t_env_list	*init_env_list(void)
{
	t_env_list	*list;

	list = ft_calloc(1, sizeof(t_env_list));
	// list = malloc(sizeof(t_env_list)); // OLD
	if (!list)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	list->next = NULL;
	return (list);
}


#include "../../includes/minishell.h"

static void	add_env_node_from_envp(t_env_list *list, char *envp_line)
{
	size_t	name_len;
	char	*var_name;
	char	*var_value;

	name_len = ft_strchr(envp_line, '=') - envp_line;
	var_name = ft_substr(envp_line, 0, name_len);
	var_value = ft_strdup(ft_strchr(envp_line, '=') + 1);
	if (!var_name || !var_value)
	{
		free(var_name);
		free(var_value);
		ft_lstclear_env(&list, free_env_list);
		return ;
	}
	add_env_node(list, var_name, var_value);
	free(var_name);
	free(var_value);
}

t_env_list	*init_envp(char **envp)
{
	int			i;
	t_env_list	*list;

	list = init_env_list();
	if (!list)
		return (NULL);
	i = -1;
	while (envp[++i])
		add_env_node_from_envp(list, envp[i]);
	return (list);
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

void	check_env_path(char **envp)
{
	int		i;
	bool	check;

	i = 0;
	check = false;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) && envp[i][6])
		{
			check = true;
			break ;
		}
		++i;
	}
	if (!*envp)
	{
		ft_putstr_fd(RED "Error\nPATH variable not found!\n" RESET, 2);
		exit(127);
	}
	if (!check)
	{
		ft_putstr_fd(RED "Error\nInvalid PATH value!\n", 2);
		exit(127);
	}
}
