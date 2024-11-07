/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:13 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 12:57:29 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	if (lst == NULL)
		return (0);
	return (ft_lstsize(lst->next) + 1);
}
/*
int main()
{
    t_list *node1 = malloc(sizeof(t_list));
    t_list *node2 = malloc(sizeof(t_list));
    t_list *node3 = malloc(sizeof(t_list));

    node1->content = "first";
    node1->next = node2;

    node2->content = "second";
    node2->next = node3;

    node3->content = "third";
    node3->next = NULL;

    printf("Taille de la liste : %d\n", ft_lstsize(node1));

    free(node1);
    free(node2);
    free(node3);

    return 0;
}
*/
