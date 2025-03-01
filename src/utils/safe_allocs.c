/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:53:25 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 09:40:14 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*safe_calloc(size_t count, size_t size, t_tracking_scope scope,
		t_shell *sh)
{
	return (safe_alloc(ft_calloc(count, size), scope, sh));
}

void	track_alloc(void *pointer, t_tracking_scope scope, t_shell *sh)
{
	t_list	*new_node;

	new_node = ft_lstnew(pointer);
	check_node_alloc(new_node, pointer, sh);
	ft_lstadd_front(&sh->allocated_pointers[scope], new_node);
}

void	*safe_alloc(void *pointer, t_tracking_scope scope, t_shell *sh)
{
	if (!pointer)
		error("Memory allocation", strerror(errno), EXIT_FAILURE, sh);
	if (scope != ONLY_CHECK)
		track_alloc(pointer, scope, sh);
	return (pointer);
}
