/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/20 19:29:12 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

bool	should_break(char c, bool in_quote)
{
	if (in_quote)
		return (false);
	if (is_special_operator(c) || is_blank(c))
		return (true);
	return (false);
}

static t_token	*init_token(char *value, t_token_type type)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	token->filtered = NULL;
	token->is_freed = false;
	return (token);
}

t_token	*create_token(t_token_type type, char *input, size_t len)
{
	char	*value;
	t_token	*token;

	value = ft_calloc(len + 1, sizeof(char));
	if (!value)
	{
		printf("Failed to allocate token value\n");
		return (NULL);
	}
	ft_strlcpy(value, input, len + 1);
	value[len] = '\0';
	token = init_token(value, type);
	if (!token)
	{
		printf("Failed to initialize token\n");
		free(value);
		return (NULL);
	}
	return (token);
}

static int	add_next_token(char *input, int *i, t_token **token_list,
							t_shell *sh)
{
	t_token			*token;
	t_token_type	type;
	int				len;

	len = 0;
	while (is_blank(input[*i]))
		(*i)++;
	if (!input[*i])
		return (EXIT_SUCCESS);
	type = get_next_token(input + *i, &len, sh);
	if (type == ERROR)
		return (report_syntax_error(sh));
	token = create_token(type, input + *i, len);
	if (!token)
	{
		ft_lstclear_token(token_list, free);
		return (report_syntax_error(sh));
	}
	ft_lstadd_back_token(token_list, token);
	*i += len;
	return (EXIT_SUCCESS);
}

int	lexer(char *input, t_token **token_list, t_shell *sh)
{
	int	i;
	int	status;

	i = 0;
	*token_list = NULL;
	while (input[i])
	{
		status = add_next_token(input, &i, token_list, sh);
		if (status != EXIT_SUCCESS)
		{
			ft_lstclear_token(token_list, free);
			return (status);
		}
	}
	return (EXIT_SUCCESS);
}
