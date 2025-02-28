/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:08:43 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:17:31 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	expand_one_arg(char *str, t_list **expanded_args, t_shell *sh)
{
	t_exp	exp;

	init_exp(&exp, str, expanded_args, sh);
	while (str[exp.i])
	{
		if (exp.context == NO_QUOTE)
			no_quote_state(str, &exp, sh);
		else if (exp.context == IN_SINGLE_QUOTE)
			single_quote_state(str, &exp);
		else if (exp.context == IN_DOUBLE_QUOTE)
			double_quote_state(str, &exp, sh);
		if (str[exp.i])
			exp.i++;
	}
	if (exp.context != NO_QUOTE)
		error("expand", "unexpected unclosed quote", EXIT_FAILURE, sh);
	add_token_to_list(&exp, sh);
}

void	no_quote_state(char *str, t_exp *exp, t_shell *sh)
{
	if (str[exp->i] == '~')
		expand_tilde(str, exp, sh);
	else if (str[exp->i] == '$')
		expand_var(str, exp, sh);
	else if (str[exp->i] == ' ')
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
			saved_wildcards_position("*", exp, sh);
		exp->buf[exp->buf_i++] = str[exp->i];
	}
}

void	single_quote_state(char *str, t_exp *exp)
{
	if (str[exp->i] == '\'')
	{
		if (exp->buf_i == 0)
			exp->empty_quotes = true;
		exp->context = NO_QUOTE;
	}
	else
		exp->buf[exp->buf_i++] = str[exp->i];
}

void	double_quote_state(char *str, t_exp *exp, t_shell *sh)
{
	if (str[exp->i] == '$')
		expand_var(str, exp, sh);
	else if (str[exp->i] == '\"')
	{
		if (exp->buf_i == 0)
			exp->empty_quotes = true;
		exp->context = NO_QUOTE;
	}
	else if (str[exp->i] == '\\'
		&& (str[exp->i + 1] == '\"' || str[exp->i + 1] == '\\'))
	{
		exp->i++;
		exp->buf[exp->buf_i++] = str[exp->i];
	}
	else
		exp->buf[exp->buf_i++] = str[exp->i];
}
