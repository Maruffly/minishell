/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/04 12:34:46 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../includes/token.h"

void	skip_whitespace(char *line, int *pos)
{
	while (line[*pos] && is_blank(line[*pos]))
		(*pos)++;
}

t_token_type	get_token_type(char *token) // int is_first_token
{
	if (is_NULL(token))
		return (0);
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token, "&&") == 0)
		return (AND);
	if (ft_strcmp(token, "||") == 0)
		return (OR);
	if (ft_strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIRECT_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (APPEND_OUT);
	if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(token, "(") == 0)
		return (OPEN_PARENTHESIS);
	if (ft_strcmp(token, ")") == 0)
		return (CLOSE_PARENTHESIS);
	if (is_variable(token, 0))
		return (LIMITER);
	// if (is_first_token)
	// 	return (CMD);
	return (ARG);
}

/* ///////////////// ANCIENNE VERSION
t_token_type	get_token_type(char *token)
{
	if (is_NULL(token))
		return (0);
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token, "&&") == 0)
		return (AND);
	if (ft_strcmp(token, "||") == 0)
		return (OR);
	if (ft_strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIRECT_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (APPEND_OUT);
	if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(token, "(") == 0)
		return (OPEN_PARENTHESIS);
	if (ft_strcmp(token, "(") == 0)
		return (CLOSE_PARENTHESIS);
	if (is_variable(token, 0))
		return (LIMITER);
	if (is_word(token, 0))
		return (CMD);
	return (ARG);
}
*/


char	*extract_word(char *line, int pos)
{
	int	start;

	start = pos;
	while (line[pos] && !is_blank(line[pos]) && !is_special_operator(line[pos]))
		pos++;
	return (ft_substr(line, start, pos - start));
}

char	*get_next_token(char *line, int pos)
{
	skip_whitespace(line, &pos);
	if (is_special_operator(line[pos]))
		return (ft_substr(line, pos, 1));
	return (extract_word(line, pos));
}
