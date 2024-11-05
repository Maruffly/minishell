/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:22 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 12:19:37 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*#include <stdio.h>
int main() 
{

    t_list *node;
    int a = 42;

    // Créer un nouveau nœud avec le contenu 'a'
    node = ft_lstnew(&a);
    if (node)
    {
        // Afficher le contenu du nœud
        printf("Contenu du nœud : %d\n", *(int *)(node->content));
    } else {
        printf("Erreur d'allocation de mémoire\n");
    }

    // Libérer la mémoire allouée pour le nœud
    free(node);

    return 0;
}
*/
