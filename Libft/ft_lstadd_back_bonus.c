/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:34:26 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 13:42:47 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*begin = NULL;
	t_list	*elem1 = ft_lstnew("lorem");
	t_list	*elem2 = ft_lstnew("ipsum");
	t_list	*elem3 = ft_lstnew("dolor");
	t_list	*elem4 = ft_lstnew("sit");
	t_list	*temp;

	ft_lstadd_back(&begin, elem1);
	ft_lstadd_back(&begin, elem2);
	ft_lstadd_back(&begin, elem3);
	ft_lstadd_back(&begin, elem4);

	temp = begin;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}

	return (0);
}
*/
