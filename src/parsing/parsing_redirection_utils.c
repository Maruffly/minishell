/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:06:27 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/24 18:43:58 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*skip_invalid_redirection(t_token **cur, t_ast *new_redir)
{
	free_ast(new_redir);
	*cur = (*cur)->next->next;
	return (NULL);
}

t_token	*parse_single_redirection(t_token *cur, t_ast **first,
									t_ast **last, t_shell *sh)
{
	if (!cur->next || !is_word(cur->next))
	{
		syntax_error(cur->value, sh);
		return (cur);
	}
	if (!validate_and_create_redirection(&cur, first, last, sh))
		return (cur);
	return (cur);
}
