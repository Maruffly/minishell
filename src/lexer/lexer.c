/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:46:34 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/15 14:19:43 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	print_token(t_token *list)
{
	t_token *current = list;

	while (current)
	{
		printf("value : %s\n", current->value);
		current = current->next;
	}
}

int	lexer(char *input, t_token **token_list, t_shell *sh)
{
	t_token			*token;
	t_token_type	type;
	int				i;
	int				len;

	i = 0;
	*token_list = NULL;
	while (input[i])
	{
		len = 0;
		while (is_blank(input[i]))
			i++;
		if (!input[i])
			break ;
		type = get_next_token(input + i, &len, sh);
		if (type == ERROR)
			return (report_syntax_error(sh));
		token = create_token(type, input + i, len);
		if (!token)
			return (report_syntax_error(sh));
		ft_lstadd_back_token(token_list, token);
		i += len;
	}
	return (EXIT_SUCCESS);
}

t_token *init_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*create_token(t_token_type type, char *input, size_t len)
{
	char	*value;
	t_token	*token;

	value = ft_calloc(len + 1, sizeof(char));
	if (!value)
		return (NULL);
	ft_strlcpy(value, input, len + 1);
	value[len] = '\0';
	token = init_token(value, type);
	if (!token)
		return (free(value), NULL);
	return (token);
}
