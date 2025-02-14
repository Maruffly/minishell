/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:26:38 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/14 17:09:25 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

void	handle_malloc_error(void)
{
	perror("malloc failed");
	exit(EXIT_FAILURE);
}

void	handle_strdup_error(void *ptr)
{
	if (!ptr)
	{
		perror("strdup failed");
		exit(EXIT_FAILURE);
	}
}

char	*handle_exit_status(t_shell *sh, t_expand *exp)
{
	char	*tmp;

	tmp = ft_itoa(sh->last_status);
	exp->i += 2;
	return (tmp);
}
