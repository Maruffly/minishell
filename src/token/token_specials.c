/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:33 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/12 16:57:24 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"


bool	is_special_operator(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (true);
	return (false);
}

bool	is_redirect(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
			|| token->type == APPEND_OUT || token->type == HEREDOC);
}

bool	is_operator(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == AND || token->type == OR);
}


bool	is_open_parenthesis(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == OPEN_PARENTHESIS);
}

bool	is_close_parenthesis(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == CLOSE_PARENTHESIS);
}
