/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/21 10:50:52 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

void	print_env_list(t_env_list *list)
{
	t_env_node	*cur;

	cur = list->head;
	while (cur)
	{
		if (cur->var_name && cur->var_value)
			printf("%s=%s\n", cur->var_name, cur->var_value);
		cur = cur->next;
	}
}

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

t_env_list	*envp_to_list(char **envp)
{
	size_t 		name_len;
	char		*var_name;
	char		*var_value;
	int			i;
	t_env_list	*list;

	list = init_env_list();
	i = -1;
	while(envp[++i])
	{
		name_len = ft_strchr(envp[i], '=') - envp[i];
		var_name = ft_substr(envp[i], 0, name_len);
		var_value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		add_env_node(list, var_name, var_value);
		free(var_name);
		free(var_value);
	}
	return (list);
}

t_env_node	*find_env_node(t_env_list *list, char *name)
{
	t_env_node	*cur;

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
