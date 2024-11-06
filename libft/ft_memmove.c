/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:47:22 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 12:10:40 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;

	if (!dest && !src)
		return (NULL);
	if ((char *)dest < (char const *)src)
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char const *)src)[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			((char *)dest)[n] = ((char const *)src)[n];
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

void *ft_memmove(void *dest, const void *src, size_t n);

int main() {
    char src[] = "wesh bienouquoi";
    char dest[20];

    ft_memmove(dest, src, strlen(src) + 1); // null terminated
    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    ft_memmove(src + 7, src, 8); // Example overlap
    printf("Overlap: %s\n", src);

    return 0;
}
*/
