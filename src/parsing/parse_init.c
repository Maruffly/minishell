/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 10:08:52 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_ast_node(t_ast **node, t_ast_type type, t_shell *sh)
{
	*node = safe_calloc(1, sizeof(t_ast), PROMPT, sh);
	(*node)->type = type;
}

int	parser(t_list *token_list, t_ast **ast, t_shell *sh)
{
	*ast = parse_logical(&token_list, sh);
	if (token_list)
		set_syntax_error(value(token_list), sh);
	if (sh->parsing_error)
		return (report_syntax_error(sh));
	return (EXIT_SUCCESS);
}
