/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:05:15 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 20:05:47 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_prompt(char *user_input, t_shell *sh)
{
	t_list	*token_list;
	t_ast	*ast;
	int		status;

	status = lexer(user_input, &token_list, sh);
	if (status == EXIT_SUCCESS && token_list)
	{
		status = parser(token_list, &ast, sh);
		if (status == EXIT_SUCCESS && ast)
		{
			status = execute_heredocs(ast, sh);
			if (status == EXIT_SUCCESS)
				status = execute(ast, O_RETURN, sh);
		}
	}
	return (status);
}
