/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/21 09:49:46 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"


char	*expand_env_var(char *str, t_expand *exp, t_shell *sh)
{
	char		*name;
	char		*env_value;
	t_env_list	*env_token;

	if (!str || !exp || !sh)
		return (NULL);
	name = get_valid_name(str, exp, sh);
	if (!name)
		return (NULL);
	env_token = find_env_node(sh->env, name);
	if (!env_token || !env_token->var_value) 
	{
		free(name);
		return (NULL);
	}
	env_value = env_token->var_value;
	exp->i += ft_strlen(name);
	free(name);
	return (env_value);
}


void	expand_var(char *str, t_expand *exp, t_shell *sh)
{
	char	*value;

	if (!
	str || !exp || !sh)
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
		if (exp->context == NO_QUOTE && exp->i > 0 && str[exp->i - 1] == '\"' && str[exp->i + ft_strlen(value) + 1] == '\"')
		{
			add_var_to_buffer("\"", exp, sh);
			add_var_to_buffer(value, exp, sh);
			add_var_to_buffer("\"", exp, sh);
		}
		else
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

char *expand_heredoc_vars(char *line, t_shell *sh, t_expand *exp)
{
	char	*result;

	if (!line || !sh || !exp)
		return (NULL);
	if (!init_expansion(exp, 0, 0, sh))
	{
		 printf("Expansion initialization failed\n"); 
		return (NULL);
	}
	while (line[exp->i])
	{
		if (line[exp->i] == '$' && line[exp->i + 1] && line[exp->i + 1] != ' ')
		{
			exp->i++;
			if (line[exp->i] == '?')
				expand_last_status(exp, sh);	
			else
				expand_env_var(line, exp, sh);
		}
		else
		{
			if (exp->buf_i < exp->buf_size - 1)
				exp->buf[exp->buf_i++] = line[exp->i];
			exp->i++;
		}
	}
	exp->buf[exp->buf_i] = '\0';
	result = ft_strdup(exp->buf);
	free(exp->buf);
	return (result);
}
