/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:48:58 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/12 16:03:47 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmb, size_t size)
{
	char	*tab;
	size_t	i;

	if (nmb && size && nmb > UINT_MAX / size)
		return (NULL);
	tab = malloc(nmb * size);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tab[i++] = 0;
	}
	return (tab);
}
