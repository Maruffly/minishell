/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:33 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/11 16:41:31 by jmaruffy         ###   ########.fr       */
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
	if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
		|| token->type == APPEND_OUT || token->type == HEREDOC)
			return (true);
		return (false);
}

bool	is_operator(t_token *token)
{
	if (token->type == AND || token->type == OR)
			return (true);
		return (false);
}

bool	is_open_parenthesis(t_token *token)
{
	if (token->type == OPEN_PARENTHESIS)
			return (true);
		return (false);
}

bool	is_close_parenthesis(t_token *token)
{
	if (token->type == CLOSE_PARENTHESIS)
			return (true);
		return (false);
}
