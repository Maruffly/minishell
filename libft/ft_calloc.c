/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:48:58 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/11 14:34:08 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmb, size_t size)
{
	char	*tab;
	size_t	total_size;

	if (nmb > UINT_MAX / size)
		return (NULL);
	total_size = nmb * size;
	tab = malloc(total_size);
	if (tab == NULL)
		return (NULL);
	memset(tab, 0, total_size);
	return (tab);
}
