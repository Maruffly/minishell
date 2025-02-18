/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:05:33 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/18 10:38:17 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_back_token(t_token **token_list, t_token *new_token)
{
	t_token	*last;

	if (!token_list || !new_token)
		return ;
	if (*token_list == NULL)
	{
		*token_list = new_token;
		new_token->prev = NULL;
	}
	else
	{
		last = *token_list;
		while (last->next)
			last = last->next;
		last->next = new_token;
		new_token->prev = last;
	}
	new_token->next = NULL;
}

void	ft_lstdelone_token(t_token *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	if (lst->value)
		del(lst->value);
	free(lst);
}

void	ft_lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (*lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_token(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

int	ft_lstsize_token(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	add_front_token(t_token **token_list, t_ast *node, t_shell *sh)
{
	t_token	*new_token;

	(void)sh;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return ;
	new_token->node = node;
	new_token->next = *token_list;
	if (*token_list)
		(*token_list)->prev = new_token;
	*token_list = new_token;
}
