/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_arg_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:12:59 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 10:09:28 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_valid_name(char *str, t_exp *exp, t_shell *sh)
{
	int		j;
	char	*name;

	j = exp->i + 1;
	if (!ft_isalpha(str[j]) && str[j] != '_')
		return (NULL);
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	name = safe_alloc(ft_substr(str, exp->i + 1, j - exp->i - 1), PROMPT, sh);
	return (name);
}

char	*expand_env_var(char *str, t_exp *exp, t_shell *sh)
{
	char	*name;
	char	*env_value;

	name = get_valid_name(str, exp, sh);
	if (name == NULL)
	{
		exp->buf[exp->buf_i++] = str[exp->i];
		exp->buf[exp->buf_i] = '\0';
		return (NULL);
	}
	env_value = value(env_var(name, sh->env));
	exp->i += ft_strlen(name);
	return (env_value);
}
