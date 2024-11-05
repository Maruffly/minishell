/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:08:50 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 14:43:13 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_obj;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_obj = ft_lstnew(f(lst->content));
		if (!new_obj)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_obj);
		lst = lst->next;
	}
	return (new_list);
}
/*
void	*square(void *num_ptr) 
{
	int	*num = (int *)num_ptr;
	int	*result = (int *)malloc(sizeof(int));
	if (result) 
		*result = (*num) * (*num);
	return result;
}

// Example function to delete an integer
void delete_int(void *num_ptr) {
    free(num_ptr);
}
int main() {
    // Create a sample list of integers
    t_list *lst = ft_lstnew((void *)malloc(sizeof(int)));
    *((int *)lst->content) = 1;
    ft_lstadd_back(&lst, ft_lstnew((void *)malloc(sizeof(int))));
    *((int *)(lst->next->content)) = 2;
    ft_lstadd_back(&lst, ft_lstnew((void *)malloc(sizeof(int))));
    *((int *)(lst->next->next->content)) = 3;

    // Map each element of the list to its square
    t_list *mapped_list = ft_lstmap(lst, &square, &delete_int);

    // Print the mapped list
    printf("Mapped list: ");
    t_list *temp = mapped_list;
    while (temp) {
        printf("%d ", *((int *)(temp->content)));
        temp = temp->next;
    }
    printf("\n");

    // Clean up
    ft_lstclear(&lst, &delete_int);
    ft_lstclear(&mapped_list, &delete_int);

    return 0;
}
*/
