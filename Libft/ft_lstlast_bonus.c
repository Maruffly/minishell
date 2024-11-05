/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:28:15 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 13:20:55 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}
/*
int main(void)
{
    t_list *first = malloc(sizeof(t_list));
    t_list *second = malloc(sizeof(t_list));
    t_list *third = malloc(sizeof(t_list));

    first->content = "Premier";
    first->next = second;
    second->content = "Deuxième";
    second->next = third;
    third->content = "Troisième";
    third->next = NULL; // Dernier elem : next = NULL

    t_list *last_element = ft_lstlast(first);

    printf("Le dernier élément est : %p\n", (void *)last_element);
    printf("Le dernier élément contient : %s\n", (char *)last_element->content);

    free(first);
    free(second);
    free(third);

    return (0);
}
*/
