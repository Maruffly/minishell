/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_arg_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:12:59 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/10 20:00:18 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	no_quote(char *str, t_expand *exp, t_shell *sh)
{
	if (!str || !exp || !sh)
		return ;
	if (str[exp->i] == '$' && exp->context != IN_SINGLE_QUOTE)
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
			save_wildcards_pos(str + exp->i, exp, sh);
		exp->buf[exp->buf_i++] = str[exp->i];
	}
}

static void	single_quote(char *str, t_expand *exp)
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

static void	double_quote(char *str, t_expand *exp, t_shell *sh)
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
	else if (str[exp->i] == '\\'
		&& (str[exp->i + 1] == '\"' || str[exp->i + 1] == '\\'))
	{
		exp->i++;
		exp->buf[exp->buf_i++] = str[exp->i];
	}
	else
		exp->buf[exp->buf_i++] = str[exp->i];
}

void	arg_expansion(char *str, t_token **expanded_args, t_shell *sh)
{
	t_expand	exp;

	if (!str || !expanded_args || !sh)
		return ;
	if (!init_expansion(&exp, str, expanded_args, sh))
		return ;
	ft_bzero(exp.buf, exp.buf_size);
	exp.buf_i = 0;
	while (str[exp.i])
	{
		if (exp.context == NO_QUOTE)
			no_quote(str, &exp, sh);
		else if (exp.context == IN_SINGLE_QUOTE)
			single_quote(str, &exp);
		else if (exp.context == IN_DOUBLE_QUOTE)
			double_quote(str, &exp, sh);
		if (str[exp.i])
			exp.i++;
	}
	if (exp.context != NO_QUOTE)
		error("expansion", "unclosed quote", EXIT_FAILURE, sh);
	add_token_to_list(&exp, sh);
}
