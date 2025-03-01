/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:35:01 by jbmy              #+#    #+#             */
/*   Updated: 2025/03/01 09:45:43 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer(char *input, t_list **token_list, t_shell *sh)
{
	t_token			*token;
	t_token_type	type;
	size_t			i;
	size_t			len;

	i = 0;
	*token_list = NULL;
	while (input[i])
	{
		len = 0;
		if (!is_space(input[i]))
		{
			type = get_next_token(input + i, &len, sh);
			if (type == ERROR)
				return (report_syntax_error(sh));
			token = create_token(type, input + i, len, sh);
			safe_lst_addback(token, token_list, PROMPT, sh);
		}
		else
			len++;
		i += len;
	}
	return (EXIT_SUCCESS);
}

t_token	*create_token(t_token_type type, char *value, size_t len, t_shell *sh)
{
	t_token	*token;

	token = safe_calloc(1, sizeof(t_token), PROMPT, sh);
	token->type = type;
	token->value = safe_alloc(ft_substr(value, 0, len), PROMPT, sh);
	return (token);
}
