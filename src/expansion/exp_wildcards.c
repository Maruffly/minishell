/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wildcards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:12 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/15 17:34:43 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_wildcard_pos(t_token **token_list, int pos, t_shell *sh)
{
	t_token	*new_token;

	(void)sh;
	if (!token_list || !sh)
		return ;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = ft_itoa(pos);
	if (!new_token->value)
	{
		free(new_token);
		return ;
	}
	ft_lstadd_back_token(token_list, new_token);
}

void	save_wildcards_pos(char *to_check, t_expand *exp, t_shell *sh)
{
	int	i;

	(void)sh;
	if (!to_check || !exp ||!sh)
		return ;
	i = 0;
	if (exp->context != NO_QUOTE)
		return ;
	while (to_check[i])
	{
		if (to_check[i] == '*')
			add_wildcard_pos(&exp->wildcards_position, exp->buf_i + i, sh);
		i++;
	}
}

