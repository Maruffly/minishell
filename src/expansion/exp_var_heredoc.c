/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:58:59 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/03 18:55:45 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*copy_before_$(char *str, t_expand *exp, int start)
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
	free(var_name);
	if (!env_token || !env_token->var_value)
		return (ft_strdup(""));
	var_value = env_token->var_value;
	exp->i += ft_strlen(var_name);
	return (ft_strdup(var_value));
}

char *expand_heredoc_vars(char *str, t_shell *sh, t_expand *exp)
{
	char	*result;
	char	*tmp;
	int		j;
	bool		in_quotes;

	in_quotes = false;
	j = 0;
	if (!str || !sh || !exp)
		return (NULL);
	if (!init_expansion(exp, 0, 0, sh))
		return (NULL);
	while (str[exp->i])
	{
		if (str[exp->i] == '$' && str[exp->i + 1] && str[exp->i + 1] != ' ')
		{
			tmp = copy_before_$(str, exp, j);
			printf("tmp after copy before $ = %s\n", tmp);
			if (tmp)
			{
				add_to_buffer(tmp, exp);
				free(tmp);
			}
			exp->i++;
			if (str[exp->i] == '?')
				tmp = handle_exit_status(sh, exp);
			else
				tmp = handle_variable(str, exp, sh);
			printf("tmp after handle variable = %s\n", tmp);
			if (tmp)
			{
				add_to_buffer(tmp, exp);
				free(tmp);
			}
			j = exp->i;
		}
		else
			exp->i++;
	}
	tmp = ft_substr(str, j, exp->i - j);
	printf("tmp after ft_substr = %s\n", tmp);
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

