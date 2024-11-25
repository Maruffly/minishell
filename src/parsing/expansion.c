/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:24:56 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/25 13:36:26 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

char	*expand_env_variable(char *input, int *pos, t_env_list *env_list)
{
	char		*key;
	char		*value;
	t_env_node	*env_node;

	key = NULL;
	value = NULL;
	while (input[*pos] && (ft_isalnum(input[*pos]) || input[*pos] == '_'))
	{
		add_char_to_value(&key, input[*pos]);
		(*pos)++;
	}
	if (key)
	{
		env_node = find_env_node(env_list, key);
		if (env_node)
			value = ft_strdup(env_node->var_value);
		free(key);
	}
	return (value);
}

char	*expand_exit_status(int *pos, int exit_status)
{
	char	*status_str;

	status_str = ft_itoa(exit_status);
	(*pos)++;
	return (status_str);
}

void	add_expanded_value(char **value, char *expanded_value)
{
	while (*expanded_value)
	{
		add_char_to_value(value, *expanded_value);
		expanded_value++;
	}
}

void	handle_expansion(char *input, int *pos, char **value, 
						t_env_list *env_list, int exit_status)
{
	char	*expanded_value;

	expanded_value = NULL;
	(*pos)++; // skip $
	if (input[*pos] == '?')
		expanded_value = expand_exit_status(pos, exit_status);
	else
		expanded_value = expand_env_variable(input, pos, env_list);
	if (expanded_value)
	{
		add_expanded_value(value, expanded_value);
		free(expanded_value);
	}
}
