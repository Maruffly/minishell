/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:48:28 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/18 11:56:34 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_logical(t_ast_logical *logical, t_shell *sh)
{
	int	left;
	int	right;

	left = execute(logical->left, KEEP_RUNNING, sh);
	sh->last_status = left;
	if (logical->operator == AND)
	{
		if (left != EXIT_SUCCESS)
			return (left);
		right = execute(logical->right, KEEP_RUNNING, sh);
		sh->last_status = right;
		return (right);
	}
	else if (logical->operator == OR)
	{
		if (left == EXIT_SUCCESS)
			return (left);
		right = execute(logical->right, KEEP_RUNNING, sh);
		sh->last_status = right;
		return (right);
	}
	return (EXIT_FAILURE);
}
