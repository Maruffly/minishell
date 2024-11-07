/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:25:09 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 14:08:09 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
void print_content(void *content)
{
	printf("%s\n", (char *)content);
}
int main(void)
{
	t_list *lst = malloc(sizeof(t_list));
	t_list *temp; // conserve une reference debut de liste

	temp = lst;
	lst->content = "Premier";
	lst->next = malloc(sizeof(t_list));
	lst = lst->next;
	lst->content = "Deuxième";
	lst->next = NULL;

	ft_lstiter(temp, &print_content);

	free(temp->next); // libere memoire depuis debut liste (ref)
	free(temp);

	return (0);
}
*/
