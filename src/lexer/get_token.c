/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:35:01 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 20:39:15 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	get_next_token(char *input, size_t *len, t_shell *sh)
{
	if (*input == '&' || *input == '|')
		return (get_logic_and_pipe(input, *input, len, sh));
	else if (*input == '<' || *input == '>')
		return (get_redirect(input, *input, len, sh));
	else if (*input == '(' || *input == ')')
		return (get_subshell(input, len));
	return (get_word(input, len, sh));
}

t_token_type	get_subshell(char *input, size_t *len)
{
	*len += 1;
	if (*input == '(')
		return (SUBSHELL_OPEN);
	return (SUBSHELL_CLOSE);
}

t_token_type	get_logic_and_pipe(char *input, char c, size_t *len,
		t_shell *sh)
{
	while (input[*len] == c)
		*len += 1;
	if (c == '&')
	{
		if (*len == 2)
			return (AND);
		else if (*len == 1 || *len == 3)
			set_syntax_error("&", sh);
		else
			set_syntax_error("&&", sh);
	}
	else if (c == '|')
	{
		if (*len == 1)
			return (PIPE);
		else if (*len == 2)
			return (OR);
		else
			set_syntax_error("||", sh);
	}
	return (ERROR);
}

t_token_type	get_redirect(char *input, char c, size_t *len, t_shell *sh)
{
	while (input[*len] == c)
		*len += 1;
	if (c == '<' && *len == 1)
		return (REDIRECT_IN);
	else if (c == '<' && *len == 2)
		return (HEREDOC);
	else if (c == '>' && *len == 1)
		return (REDIRECT_OUT);
	else if (c == '>' && *len == 2)
		return (APPEND_OUT);
	set_syntax_error(input, sh);
	return (ERROR);
}

t_token_type	get_word(char *input, size_t *len, t_shell *sh)
{
	char	c;
	bool	in_quote;

	in_quote = false;
	while (input[*len])
	{
		if (input[*len + 1] && input[*len] == '\\')
			*len += 1;
		else if (input[*len] == '\"' || input[*len] == '\'')
		{
			if (!in_quote)
			{
				c = input[*len];
				in_quote = true;
			}
			else if (in_quote && input[*len] == c)
				in_quote = false;
		}
		else if ((is_token(input[*len]) || is_space(input[*len])) && !in_quote)
			break ;
		*len += 1;
	}
	if (in_quote)
		return (set_syntax_error("unclosed quote", sh), ERROR);
	return (WORD);
}
