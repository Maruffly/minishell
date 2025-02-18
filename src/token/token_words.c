/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:02:12 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/18 10:38:50 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

bool	is_word(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == WORD);
}

char	*get_token_string(t_token_type type)
{
	if (type == PIPE)
		return ("|");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	else if (type == OPEN_PARENTHESIS)
		return ("(");
	else if (type == CLOSE_PARENTHESIS)
		return (")");
	else if (type == WORD)
		return ("word");
	else if (type == REDIRECT_IN)
		return ("<");
	else if (type == REDIRECT_OUT)
		return (">");
	else if (type == APPEND_OUT)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == WILDCARD)
		return ("*");
	else
		return ("[unknown token]");
}
