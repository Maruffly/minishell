/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:04:13 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 13:48:45 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
/*
int main(void)
{
	void *del = NULL;
    // Création d'un élément de la liste
    t_list *elem = (t_list *)malloc(sizeof(t_list));
    if (!elem)
    {
        printf("Erreur d'allocation de mémoire\n");
        return 1;
    }

    // Allocation et initialisation du contenu de l'élément
    int *content = (int *)malloc(sizeof(int));
    if (!content)
    {
        free(elem);
        printf("Erreur d'allocation de mémoire\n");
        return 1;
    }
    *content = 42;
    elem->content = content;
    elem->next = NULL;

    // Suppression de l'élément
    ft_lstdelone(elem, del);

    return 0;
}
*/
