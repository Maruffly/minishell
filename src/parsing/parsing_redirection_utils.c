/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:06:27 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/24 15:41:08 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*skip_invalid_redirection(t_token **cur, t_ast *new_redir)
{
	free_ast(new_redir);
	*cur = (*cur)->next->next;
	return (NULL);
}
