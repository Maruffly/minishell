/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:58:59 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/14 14:29:31 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*copy_before_dollar(char *str, t_expand *exp, int start)
{
	char	*tmp;

	tmp = ft_substr(str, start, exp->i - start);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*handle_exit_status(t_shell *sh, t_expand *exp)
{
	char	*tmp;

	tmp = ft_itoa(sh->last_status);
	exp->i += 2;
	return (tmp);
}

static char	*handle_variable(char *str, t_expand *exp, t_shell *sh)
{
	char		*var_value;
	char		*var_name;
	t_env_list	*env_token;

	(void)exp;
	var_name = get_valid_name(str, exp, sh);
	if (!var_name)
		return (NULL);
	env_token = find_env_node(sh->env, var_name);
	if (!env_token || !env_token->var_value)
	{
		exp->expandable = false;
		return (NULL);
	}
	var_value = env_token->var_value;
	exp->i += ft_strlen(var_name);
	free(var_name);
	return (ft_strdup(var_value));
}

static void	process_dollar_expansion(char *str, t_expand *exp,
									t_shell *sh, int *j)
{
	char	*tmp;
	char	*var_value;

	tmp = copy_before_dollar(str, exp, *j);
	if (tmp)
	{
		add_to_buffer(tmp, exp);
		free(tmp);
	}
	exp->i++;
	if (str[exp->i] == '?')
		var_value = handle_exit_status(sh, exp);
	else
		var_value = handle_variable(str, exp, sh);
	if (var_value)
	{
		add_to_buffer(var_value, exp);
		free(var_value);
	}
	else
	{
		while (str[exp->i] && (ft_isalnum(str[exp->i]) || str[exp->i] == '_'))
			exp->i++;
	}
	*j = exp->i;
}

char	*store_to_buffer(char *tmp, t_expand *exp)
{
	char	*result;

	if (tmp)
	{
		add_to_buffer(tmp, exp);
		free(tmp);
	}
	exp->buf[exp->buf_i] = '\0';
	result = ft_strdup(exp->buf);
	free(exp->buf);
	return (result);
}

char	*expand_heredoc_vars(char *str, t_shell *sh, t_expand *exp)
{
	int		j;
	char	*tmp;
	bool	to_expand;

	j = 0;
	to_expand = false;
	while (str[exp->i])
	{
		if (str[exp->i] == '$' && str[exp->i + 1] && str[exp->i + 1] != ' ')
		{
			process_dollar_expansion(str, exp, sh, &j);
			to_expand = true;
		}
		else
			exp->i++;
	}
	if (str[j] && j < exp->i && to_expand)
	{
		tmp = ft_substr(str, j, exp->i - j);
		if (tmp && *tmp)
			add_to_buffer(tmp, exp);
		free(tmp);
	}
	if (exp->buf_i == 0)
		return (ft_strdup(str));
	return (store_to_buffer(NULL, exp));
}
