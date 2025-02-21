/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:08:43 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/19 16:38:25 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	no_quote(char *str, t_expand *exp, t_shell *sh)
{
	if (!str || !exp || !sh)
		return ;
	if (str[exp->i] == '$' && exp->context != IN_SINGLE_QUOTE)
		expand_var(str, exp, sh);
	else if (str[exp->i] == ' ' && exp->context == NO_QUOTE)
		add_token_to_list(exp, sh);
	else if (str[exp->i] == '\"')
		exp->context = IN_DOUBLE_QUOTE;
	else if (str[exp->i] == '\'')
		exp->context = IN_SINGLE_QUOTE;
	else if (str[exp->i] == '\\')
		exp->buf[exp->buf_i++] = str[++exp->i];
	else
	{
		if (str[exp->i] == '*')
			save_wildcards_pos(str + exp->i, exp, sh);
		exp->buf[exp->buf_i++] = str[exp->i];
	}
}

void	single_quote(char *str, t_expand *exp)
{
	if (!str || !exp)
		return ;
	if (str[exp->i] == '\'')
	{
		if (exp->buf_i == 0)
			exp->empty_quotes = true;
		exp->context = NO_QUOTE;
	}
	else
		exp->buf[exp->buf_i++] = str[exp->i];
}

void	double_quote(char *str, t_expand *exp, t_shell *sh)
{
	if (!str || !exp || !sh)
		return ;
	if (str[exp->i] == '$')
		expand_var(str, exp, sh);
	else if (str[exp->i] == '\"')
	{
		if (exp->buf_i == 0)
			exp->empty_quotes = true;
		exp->context = NO_QUOTE;
	}
	else if (str[exp->i] == '\\' && (str[exp->i + 1] == '\"'
			|| str[exp->i + 1] == '\\'))
	{
		exp->i++;
		exp->buf[exp->buf_i++] = str[exp->i];
	}
	else
		exp->buf[exp->buf_i++] = str[exp->i];
}

static void	create_and_add_token(t_expand *exp)
{
	char	*content;
	t_token	*new_token;

	content = NULL;
	if (exp->buf_i > 0)
		content = ft_strdup(exp->buf);
	else
		content = ft_strdup("");
	if (!content)
		return ;
	new_token = create_token(WORD, content, ft_strlen(content));
	if (!new_token)
		return (free(content));
	ft_lstadd_back_token(exp->tokens, new_token);
	exp->buf_i = 0;
	exp->empty_quotes = false;
	free(content);
}

void	*add_token_to_list(t_expand *exp, t_shell *sh)
{
	if (!exp || !sh)
		return (NULL);
	if (exp->wildcards_position)
		filename_expansion(exp, sh);
	if (!exp->wildcards_position || (exp->buf_i > 0 && !exp->has_match))
		create_and_add_token(exp);
	if (exp->buf)
	{
		free(exp->buf);
		exp->buf = NULL;
	}
	if (exp->wildcards_position)
	{
		free_wildcards(exp->wildcards_position);
		exp->wildcards_position = NULL;
	}
	return (NULL);
}
