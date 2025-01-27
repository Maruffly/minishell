/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/27 09:40:31 by jlaine           ###   ########.fr       */
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
