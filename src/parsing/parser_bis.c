/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:06:27 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:21:13 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parse_logical(t_list **token, t_shell *sh)
{
	t_ast			*left;
	t_token_type	logical_operator;
	t_ast			*right;

	left = parse_pipeline(token, sh);
	while (is_type(token, 2, AND, OR))
	{
		logical_operator = type(*token);
		*token = (*token)->next;
		right = parse_pipeline(token, sh);
		left = create_ast_logical(left, logical_operator, right, sh);
	}
	return (left);
}

t_ast	*parse_pipeline(t_list **token, t_shell *sh)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_redirection(token, sh);
	while (*token && type(*token) == PIPE)
	{
		*token = (*token)->next;
		right = parse_redirection(token, sh);
		left = create_ast_pipeline(left, right, sh);
	}
	return (left);
}
