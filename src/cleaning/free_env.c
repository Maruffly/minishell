/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:50:37 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/24 17:01:54 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(void *list)
{
	t_env_list	*env_list;
	t_env_list	*cur;
	t_env_list	*next;

	env_list = (t_env_list *)list;
	if (!env_list)
		return;
	cur = env_list->head;
	while (cur)
	{
		next = cur->next;
		free(cur->var_name);
		free(cur->var_value);
		free(cur);
		cur = next;
	}
	free(env_list);
}

void	ft_lstclear_env(t_env_list **lst, void (*del)(void *))
{
    if (!lst || !*lst || !del)
        return;

    del(*lst);
    *lst = NULL;
}

void ft_lstdelone_env(t_env_list *env, void (*del)(void *))
{
	if (env)
	{
		if (del)
		{
			del(env->var_name);
			del(env->var_value);
		}
		free(env);
	}
}

void	free_env_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_env_node(t_env_list *node)
{
	if (node)
	{
		free(node->var_name);
		free(node->var_value);
		free(node);
	}
}
