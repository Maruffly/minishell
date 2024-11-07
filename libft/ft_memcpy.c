/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:30:13 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/30 15:11:23 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	if (!dest && !src && n > 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

void *ft_memcpy(void *dest, const void *src, size_t n);

int main() {
    char src[] = "Hello, world!";
    char dest[20];

   // ft_memcpy("", "", strlen(src) + 1); // Including null terminator

   memcpy("", "", strlen(src) + 1);
    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}
*/
