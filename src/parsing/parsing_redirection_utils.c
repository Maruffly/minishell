/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:06:27 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/24 22:03:46 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*skip_invalid_redirection(t_token **cur, t_ast *new_redir, t_shell *sh)
{
	free_ast(new_redir);
	*cur = (*cur)->next->next;
	sh->redirection_error = true;
	return (NULL);
}

t_token	*parse_single_redirection(t_token *cur, t_ast **first,
									t_ast **last, t_shell *sh)
{
	if (!cur->next || !is_word(cur->next))
	{
		if (cur->next)
		{
			syntax_error(cur->next->value, sh);
			return (cur->next);
		}
		else
			return (NULL);
	}
	if (!validate_and_create_redirection(&cur, first, last, sh))
		return (cur);
	return (cur);
}
