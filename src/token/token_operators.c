/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:40 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/21 14:56:03 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/token.h"

int	is_separator(char *line, int i)
{
	if (line[i] == ';')
		return (1);
	return (0);
}

int	is_or_operator(char *line, int i)
{
	if (line[i] == '|' && line[i + 1] == '|')
		return (1);
	return (0);
}

int	is_and_operator(char *line, int i)
{
	if (line[i] == '&' && line[i + 1] == '&')
		return (1);
	return (0);
}

int	is_boolean_operator(char *line, int i)
{
	if (is_or_operator(line, i) || is_and_operator(line, i))
		return (1);
	return (0);
}

int	is_operator(char *line, int i)
{
	if (line[i] == '|' || line[i] == '&' || line[i] == '<' ||
		line[i] == '>' || line[i] == ';')
		return (1);
	return (0);
}
