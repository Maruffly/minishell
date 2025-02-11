/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wildcards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:12 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/11 15:44:45 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_wildcard_pos(t_wildcard **wildcards, int pos, t_shell *sh)
{
	t_wildcard	*new_wildcard;

	(void)sh;
	if (!wildcards || !sh)
		return ;
	new_wildcard = ft_calloc(1, sizeof(t_wildcard));
	if (!new_wildcard)
		return ;
	new_wildcard->position = pos;
	new_wildcard->next = *wildcards;
	*wildcards = new_wildcard;
}

void	save_wildcards_pos(char *to_check, t_expand *exp, t_shell *sh)
{
	int			i;
	t_wildcard	*new_wildcard;

	(void)sh;
	if (!to_check || !exp || !sh || exp->context != NO_QUOTE)
		return ;
	i = 0;
	while (to_check[i])
	{
		if (to_check[i] == '*')
		{
			new_wildcard = ft_calloc(1, sizeof(t_wildcard));
			if (!new_wildcard)
				return ;
			new_wildcard->position = exp->buf_i + i;
			new_wildcard->next = exp->wildcards_position;
			exp->wildcards_position = new_wildcard;
		}
		i++;
	}
}
