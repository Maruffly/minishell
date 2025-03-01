/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 10:08:22 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	type(t_list *token)
{
	return (((t_token *)token->content)->type);
}

char	*value(t_list *token)
{
	if (token == NULL)
		return (NULL);
	return (((t_token *)token->content)->value);
}

bool	is_type(t_list **token_list, int num_args, ...)
{
	va_list			args;
	t_token_type	tmp_type;

	if (token_list == NULL || *token_list == NULL)
		return (false);
	tmp_type = type(*token_list);
	va_start(args, num_args);
	while (num_args--)
	{
		if (tmp_type == va_arg(args, t_token_type))
		{
			va_end(args);
			return (true);
		}
	}
	va_end(args);
	return (false);
}

char	*type_to_string(t_token_type type)
{
	if (type == PIPE)
		return ("|");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	else if (type == SUBSHELL_OPEN)
		return ("(");
	else if (type == SUBSHELL_CLOSE)
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
	else
		return ("[unknown token]");
}
