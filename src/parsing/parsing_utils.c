/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/21 11:04:07 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_token_string(t_token_type type)
{
	if (type == PIPE)
		return ("|");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	else if (type == OPEN_PARENTHESIS)
		return ("(");
	else if (type == CLOSE_PARENTHESIS)
		return (")");
	else if (type == WORD)
		return ("word");
	else if (type == REDIRECT_IN)
		return ("<");
	else if (type == REDIRECT_OUT)
		return (">");
	else if (type == APPEND_OUT)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == WILDCARD)
		return ("*");
	else
		return ("[unknown token]");
}

void	add_arg_tab(char ***array, char *new_arg)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	while ((*array) && (*array)[i])
		i++;
	new_array = ft_calloc(i + 2, sizeof(char *));
	if (!new_array)
		return ;
	j = 0;
	while (j < i)
	{
		new_array[j] = (*array)[j];
		j++;
	}
	new_array[i] = new_arg;
	new_array[i + 1] = NULL;
	*array = new_array;
}

void	add_char_to_value(char **value, char c)
{
	size_t	len;
	char	*new_value;

	if (!value)
		return ;
	if (!*value)
	{
		*value = malloc(2); // 1 caractère + '\0'
		if (!*value)
			return ;
		(*value)[0] = c;
		(*value)[1] = '\0';
		return ;
	}
	len = ft_strlen(*value);
	new_value = malloc(len + 2);  // +1 pour nouveau char , +1 pour \0
	if (!new_value)
		return ;
	ft_strcpy(new_value, *value);
	new_value[len] = c;
	new_value[len + 1] = '\0';
	free (*value);
	*value = new_value;
}
/* bool	is_syntax_ok(t_token *new_token, t_token *head)
{
	if (!head && new_token->type == PIPE)
	{
		printf("Syntax error : unexpected token '|'\n ");
		return (false);
	}
	if (new_token->type == PIPE && (!head || !head->next))
	{
		printf("Syntax error : incomplete pipe sequence\n");
		return (false);
	}
	if ((new_token->type == REDIRECT_IN || new_token->type == REDIRECT_OUT
		|| new_token->type == APPEND_OUT || new_token->type == HEREDOC)
		&& (!head || !head->next))
		{
			ft_putstr_fd("Syntax error: invalid redirection missing argument\n", STDERR_FILENO);
			return (false);
}
	return (true);
}

bool	is_blank_line(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!is_blank(*line))
			return (false);
		line++;
	}
	return (true);
}

bool	is_empty_line(char *input)
{
	int	i;

	if (!input) // Si la ligne est NULL (sécurité supplémentaire)
		return (true);
	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (input[i] == '\0'); // Retourne true si la ligne est vide après trim
} */
