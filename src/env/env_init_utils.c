/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:39:13 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/27 09:40:26 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

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
