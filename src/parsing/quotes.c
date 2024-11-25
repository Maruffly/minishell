/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:06:09 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/25 14:28:32 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

void	add_char_to_value(char **value, char c)
{
	size_t	len;
	char	*new_value;

	if (!value || !*value)
		return ;
	len = ft_strlen(*value);
	new_value = malloc(len + 2);  // +1 pour nouveau char , +1 pour \0
	if (!new_value)
		return ;
	ft_strcpy(new_value, *value);
	new_value[len] = c;
	new_value[len + 1] = '\0';
	free (*value);
	*value = new_value;
}


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
