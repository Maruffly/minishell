/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:06:09 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/12 13:35:48 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_internal_quotes(char *input, int *pos, char **value, char c) // OK
{
	if (c == '"' && input[*pos] == '/')
	{
		(*pos)++;
		if (input[*pos])
			add_char_to_value(value, input[*pos]);
	}
	else
		add_char_to_value(value, input[*pos]);
	(*pos)++;
}

void	handle_quotes(char *input, int *pos, char **value) // OK
{
	char	c;

	c = input[*pos];
	(*pos)++;
	while (input[*pos] && input[*pos] != c)
		handle_internal_quotes(input, pos, value, c);
	if (input[*pos] == c)
		(*pos)++;
}
