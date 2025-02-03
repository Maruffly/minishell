/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/03 12:58:28 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_env_var(char *str, t_expand *exp, t_shell *sh)
{
	char *name;
	char *env_value;
	t_env_list *env_token;
	int name_len;

	if (!str || !exp || !sh)
		return (NULL);
	if (exp->context == IN_SINGLE_QUOTE)
		return (ft_strdup(str));
	name = get_valid_name(str, exp, sh);
	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	env_token = find_env_node(sh->env, name);
	if (!env_token || !env_token->var_value)
	{
		exp->i += name_len;
		return (free(name), ft_strdup(""));
	}
	env_value = env_token->var_value;
	exp->i += name_len;
	free(name);
	return (ft_strdup(env_value));
}

void	expand_var(char *str, t_expand *exp, t_shell *sh)
{
	char	*value;

	if (!str || !exp || !sh)
		return ;
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
		add_var_to_buffer(value, exp, sh);
	}
}

void	expand_last_status(t_expand *exp, t_shell *sh)
{
	char	*last_exit_status;

	if (!exp || !sh)
		return ;
	exp->i++;
	last_exit_status = ft_itoa(sh->last_status);
	if (!last_exit_status)
		return ;
	if (exp->context == NO_QUOTE && exp->buf_i == 0 && exp->i == 2)
	{
		ft_putstr_fd("Omar&Fred: ", STDERR_FILENO);
		ft_putstr_fd(last_exit_status, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
		add_var_to_buffer(last_exit_status, exp, sh);
	free(last_exit_status);
}
