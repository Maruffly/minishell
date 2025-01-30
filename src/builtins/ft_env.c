/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:34:24 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/30 15:04:54 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_list(t_env_list *list)
{
	t_env_list	*cur;

	cur = list->head;
	while (cur)
	{
		if (cur->var_name && cur->var_value)
			printf("%s=%s\n", cur->var_name, cur->var_value);
		cur = cur->next;
	}
}

void	exec_env(t_env_list *env_list)
{
	print_env_list(env_list);
}
