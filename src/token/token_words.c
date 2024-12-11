/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:02:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/11 14:47:44 by jmaruffy         ###   ########.fr       */
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

bool	is_word(t_token *token)
{
	if (token->type == WORD)
		return (true);
	return (false);
}
