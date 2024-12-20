/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:14:26 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/20 13:53:36 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_node(t_env_list *node);

void	free_env_list(void *list)
{
	t_env_list	*env_list;
	t_env_list	*cur;
	t_env_list	*next;

	if (!list)
		return ;
	env_list = (t_env_list *)list;
	if (!env_list->head)
	{
		free(list);
		return ;
	}
	cur = env_list->head;
	while (cur)
	{
		next = cur->next;
		if (cur)
			free_env_node(cur);
		cur = next;
	}
	env_list->head = NULL;
	free(list);
}

void free_token_list(t_token *tokens)
{
	t_token *temp;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}


void ft_lstclear_env(t_env_list **lst, void (*del)(void *))
{
    t_env_list *tmp;

    if (*lst == NULL || del == NULL)
        return;

    while (*lst)
    {
        tmp = (*lst)->next;
        ft_lstdelone_env(*lst, del);
        *lst = tmp;
    }
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