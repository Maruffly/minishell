/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:18:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 10:57:20 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	safe_lst_addfront(void *content, t_list **lst, t_tracking_scope scope,
	t_shell *sh)
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	check_node_alloc(new_node, content, sh);
	ft_lstadd_front(lst, new_node);
	track_alloc(new_node, scope, sh);
}

void	safe_lst_addback(void *content, t_list **lst, t_tracking_scope scope,
	t_shell *sh)
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	check_node_alloc(new_node, content, sh);
	ft_lstadd_back(lst, new_node);
	track_alloc(new_node, scope, sh);
}

void	check_node_alloc(t_list *new_node, void *pointer, t_shell *sh)
{
	if (!new_node)
	{
		free(pointer);
		error("Memory allocation", strerror(errno), EXIT_FAILURE, sh);
	}
}
