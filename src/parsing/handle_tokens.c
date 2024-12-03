/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:17:58 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/03 16:28:23 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

char	*handle_parentheses(char *input, int *pos)
{
	char	*value;

	value = ft_substr(input, (unsigned int)*pos, 1);
	(*pos)++;
	return (value);
}

void	*handle_all_tokens(char *input, int *pos, char **value, 
							t_env_list *env_list, int exit_status)
{
	while (input[*pos] && !is_blank(input[*pos]))
	{
		if (input[*pos] == '\'' || input[*pos] == '"')
			handle_quotes(input, pos, value);
		else if (input[*pos] == '$')
			handle_expansion(input, pos, value, env_list, exit_status);
		else
		{
			add_char_to_value(value, input[*pos]);
			(*pos)++;
		}
	}
	return (NULL);
}

t_token	*free_token_value(char *value)
{
	free(value);
	return (NULL);
}


bool	validate_parentheses(t_token *tokens)
{
	int	open_parentheses;
	
	open_parentheses = 0;
	while (tokens)
	{
		if (tokens->type == OPEN_PARENTHESIS)
			open_parentheses++;
		else if (tokens->type == CLOSE_PARENTHESIS)
		{
			if (open_parentheses == 0)
				return (false);
			open_parentheses--;
		}
		tokens = tokens->next;
	}
	return (open_parentheses == 0);
}


/*
t_token	*create_token(const char *input, int *pos, 
						t_env_list *env_list, int exit_status)
{
	char	*value;
	t_token	*token;

	skip_whitespace(input, pos);
	if (input[*pos] == '(' || input[*pos] == ')')
		value = handle_parentheses(input, pos);
	else
	{
		value = NULL;
		handle_all_tokens(input, pos, &value, env_list, exit_status);
	}
	if (!value)
		return (free_token_value(value));
	token = init_token(value, get_token_type(value));
	if (!token)
		return (free_token_value(value));
	return (token);
}
*/