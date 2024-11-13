/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:33 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/13 17:50:07 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/token.h"

int	is_special_char(char c)
{
	if (c == '|' || c == '&' || c == '<' ||
		c == '>' || c == ';')
		return (1);
	return (0);
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
