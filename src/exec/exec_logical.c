/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:48:28 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 19:50:40 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_logical(t_ast_logical *logical, t_shell *sh)
{
	int	left_status;
	int	right_status;

	left_status = execute(logical->left, O_RETURN, sh);
	sh->last_status = left_status;
	if (logical->operator == TK_AND)
	{
		if (left_status == EXIT_SUCCESS)
		{
			right_status = execute(logical->right, O_RETURN, sh);
			return (right_status);
		}
		return (left_status);
	}
	else if (logical->operator == TK_OR)
	{
		if (left_status != EXIT_SUCCESS)
		{
			right_status = execute(logical->right, O_RETURN, sh);
			return (right_status);
		}
		return (left_status);
	}
	return (EXIT_FAILURE);
}
