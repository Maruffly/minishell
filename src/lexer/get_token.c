/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:35:01 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/24 13:07:57 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	get_next_token(char *input, int *len, t_shell *sh)
{
	if (*input == '&' || *input == '|')
		return (get_pipe_logic(input, *input, len, sh));
	else if (*input == '<' || *input == '>')
		return (get_redirect(input, *input, len, sh));
	else if (*input == '(' || *input == ')')
		return (get_subshell(input, len));
	return (get_word(input, *input, len, sh));
}

t_token_type	get_pipe_logic(char *input, char c, int *len, t_shell *sh)
{
	while (input[*len] == c)
		*len += 1;
	if (c == '&')
	{
		if (*len == 2)
			return (AND);
		else if (*len == 1 || *len == 3)
			syntax_error("&", sh);
		else
			syntax_error("&&", sh);
	}
	else if (c == '|')
	{
		if (*len == 1)
			return (PIPE);
		else if (*len == 2)
			return (OR);
		else
			syntax_error("||", sh);
	}
	return (ERROR);
}

t_token_type	get_redirect(char *input, char c, int *len, t_shell *sh)
{
	while (input[*len] == c)
		*len += 1;
	if (input[*len] == '\0' && !is_blank(input[*len]))
	{
		syntax_error(input, sh);
		return (ERROR);
	}
	if (c == '<' && *len == 1)
		return (REDIRECT_IN);
	else if (c == '<' && *len == 2)
		return (HEREDOC);
	else if (c == '>' && *len == 1)
		return (REDIRECT_OUT);
	else if (c == '>' && *len == 2)
		return (APPEND_OUT);
	syntax_error(input, sh);
	return (ERROR);
}

t_token_type	get_subshell(char *input, int *len)
{
	*len += 1;
	if (*input == '(')
		return (OPEN_PARENTHESIS);
	else if (*input == ')')
		return (CLOSE_PARENTHESIS);
	return (ERROR);
}

t_token_type	get_word(char *input, char c, int *len, t_shell *sh)
{
	bool	in_quote;

	in_quote = false;
	*len = 0;
	while (input[*len])
	{
		if (input[*len] == '\\' && input[*len + 1])
			(*len)++;
		else if (input[*len] == '\"' || input[*len] == '\'')
			handle_quotes(input, &c, &in_quote, len);
		else if (!in_quote && should_break(input[*len], in_quote))
			break ;
		(*len)++;
	}
	if (in_quote)
		return (syntax_error("unclosed quote", sh), ERROR);
	return (WORD);
}
