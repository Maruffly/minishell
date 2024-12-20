/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wildcards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/20 15:11:42 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_wildcard_pos(t_expand *exp, int pos)
{
	t_wildcard	*new_position;
	
	new_position = ft_calloc(1, sizeof(t_wildcard));
	if (!new_position)
		return ;
	new_position->position = pos;
	new_position->next = exp->wildcards_position;
	exp->wildcards_position = new_position;
}

void	save_wildcards_pos(char *to_check, t_expand *exp, t_shell *sh)
{
	int	i;

	(void)sh;
	i = 0;
	if (exp->context == IN_SINGLE_QUOTE || exp->context == IN_DOUBLE_QUOTE)
		return ;
	while (to_check[i])
	{
		if (to_check[i])
			add_wildcard_pos(exp, exp->buf_i + 1);
		i++;
	}
}

