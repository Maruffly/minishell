/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:33 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/21 14:31:45 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/token.h"

bool	is_special_operator(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == ';')
		return (true);
	return (false);
}

int	is_parenthesis(char *line, int i)
{
	if (line[i] == '(' || line[i] == ')')
		return (1);
	return (0);
}

int	is_open_parenthesis(char *line, int i)
{
	if (line[i] == '(')
		return (1);
	return (0);
}

int	is_close_parenthesis(char *line, int i)
{
	if (line[i] == ')')
		return (1);
	return (0);
}

int	is_escaped_char(char *line, int i)
{
	if (line[i] == '\\')
		return (1);
	return (0);
}
