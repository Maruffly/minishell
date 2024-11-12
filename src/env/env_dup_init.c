/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 16:54:23 by jmaruffy         ###   ########.fr       */
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

/* int	main(int ac, char **av, char **envp)
{
	t_env_list *list;
	(void)ac;
	(void)av;

	list = envp_to_list(envp);
	print_env_list(list);
	free_env_list(list);
} */
