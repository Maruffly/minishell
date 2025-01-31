/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/31 18:31:39 by jlaine           ###   ########.fr       */
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

int	is_quoted(char *str)
{
	size_t	len;
	char	quote;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	quote = str[0];
	if ((quote == '\'' || quote == '\"') && str[len - 1] == quote)
		return (1);
	return (0);
}

void	remove_quotes(char *str)
{
	size_t	len;
	size_t	i;

	if (!str || !*str)
		return ;
	len = ft_strlen(str);
	if (len < 2)
		return ;
	if (str[0] == '\'' || str[0] == '\"')
	{
		i = 0;
		while (i < len - 1)
		{
			str[i] = str[i + 1];
			i++;
		}
		str[len - 2] = '\0';
	}
}
