/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:48:28 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/22 13:06:14 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int exec_logical(t_ast_logical *logical, t_shell *sh)
{
	int left;
	int right;

	left = execute(logical->left, KEEP_RUNNING, sh);
	sh->last_status = left;
	if (logical->operator == AND)
	{
		if (left == EXIT_SUCCESS)
		{
			right = execute(logical->right, KEEP_RUNNING, sh);
			return (right);
		}
		return (left);
	}
	else if (logical->operator == OR)
	{
		if (left != EXIT_SUCCESS)
		{
			right = execute(logical->right, KEEP_RUNNING, sh);
			return (right);
		}
		return (left);
	}
	return (EXIT_FAILURE);
}
