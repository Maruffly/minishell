/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:03:22 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/20 15:39:24 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_env_var(char *str, t_expand *exp, t_shell *sh)
{
	char		*name;
	char		*env_value;
	t_env_list	*env_token;

	name = get_valid_name(str, exp, sh);
	if (name == NULL)
	{
		exp->buf[exp->buf_i++] = str[exp->i];
		exp->buf[exp->buf_i] = '\0';
		return (NULL);
	}
	env_token = find_env_token(name, sh->env);
	if (env_token != NULL && env_token->var_value != NULL)
		env_value = env_token->var_value;
	else
		env_value = NULL;
	exp->i += ft_strlen(name);
	return (env_value);
}

void	expand_var(char *str, t_expand *exp, t_shell *sh)
{
	char	*value;

	if (str[exp->i + 1] == '?')
		expand_last_status(exp, sh);
	else if (exp->context == NO_QUOTE && (str[exp->i + 1] == '\"'
			|| str[exp->i + 1] == '\''))
		return ;
	else
	{
		value = expand_env_var(str, exp, sh);
		if (!value)
			return ;
		else if (exp->context == NO_QUOTE)
			value = word_splitting(exp, value, sh); ///// TO DO
		if (value)
			add_var_to_buffer(value, exp, sh);
	}
}

void	expand_last_status(t_expand *exp, t_shell *sh)
{
	char	*last_exit_status;
	
	exp->i++;
	last_exit_status = ft_itoa(sh->last_status);
	if (!last_exit_status)
		return ;
	add_var_to_buffer(last_exit_status, exp, sh);
}
