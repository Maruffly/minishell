/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:33 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/11 17:44:58 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parsing.h"
#include "../includes/builtins.h"
#include "../includes/minishell.h"

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
