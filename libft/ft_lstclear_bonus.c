/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:16:23 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 14:03:04 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (*lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}
/*
int main()
{
	void	*del = NULL;
	t_list	*lst = NULL;
    // Create some nodes for demonstration
    t_list *node1 = malloc(sizeof(t_list));
    node1->content = malloc(sizeof(int));
    *(int *)(node1->content) = 10;

    t_list *node2 = malloc(sizeof(t_list));
    node2->content = malloc(sizeof(int));
    *(int *)(node2->content) = 20;

    // Link the nodes together
    node1->next = node2;
    node2->next = NULL;

    // Pass the address of the head pointer and 
    // the delete function to ft_lstclear
    t_list *head = node1;

    // head should now be NULL as the list is cleared
    if (head == NULL)
        printf("List cleared successfully.\n");
    else
        printf("List was not cleared successfully.\n");

    return 0;
}
*/
