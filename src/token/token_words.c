/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:02:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/09 13:50:15 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_NULL(char *line)
{
	if (!line || *line == '\0')
		return (1);
	return (0);
}

int	is_variable(char *line, int i)
{
	if (line[i] == '$' && line[i + 1] && !is_blank(line[i + 1]))
		return (1);
	return (0);
}

int	is_word(char *line, int i)
{
	if (!is_quote(line[i]) && !is_blank(line[i]) && line[i] != '$'
		&& !is_special_operator(line[i]) && !is_parenthesis(line, i)
		&& !is_variable(line, i))
		return (1);
	return (0);
}
