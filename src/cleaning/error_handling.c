/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:26:38 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/06 17:27:35 by jlaine           ###   ########.fr       */
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
