/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:15:53 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 14:05:44 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("%p -> ", lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

t_list	*ft_lstnew(void *content);

int main()
{
    t_list *list = NULL;

	printf("Liste avant ajouts : ");
    ft_lstprint(list);
    printf("\n");

    // Création dint main()

	printf("Liste avant ajouts : ");
    ft_lstprint(list);  //
    printf("\n");

    t_list *node1 = ft_lstnew((void *)1);
    t_list *node2 = ft_lstnew((void *)2);
    t_list *node3 = ft_lstnew((void *)3);

    // Ajout des éléments au début de la liste
    ft_lstadd_front(&list, node3); // Liste: 3 -> NULL
    ft_lstadd_front(&list, node2); // Liste: 2 -> 3 -> NULL
    ft_lstadd_front(&list, node1); // Liste: 1 -> 2 -> 3 -> NULL

    printf("Liste après ajouts : ");
    ft_lstprint(list);

    return 0;
}
*/
