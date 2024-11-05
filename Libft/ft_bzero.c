/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:13:56 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/30 11:05:46 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset((unsigned char *)s, 0, n);
}
/*
#include <stdio.h>

void *ft_memset(void *dest, int c, size_t n);

int main() {
    char buffer[0];

    ft_memset(buffer, '\0', sizeof(buffer));

    // Print the buffer to verify
  for (unsigned long i = 0; i < sizeof(buffer); i++) {
        printf("%c ", buffer[i]);
    }

    printf("\n");

    ft_bzero(buffer, sizeof(buffer));
    for (unsigned long i = 0; i < sizeof(buffer); i++) {
        printf("%c ", buffer[i]);
    }
    return 0;
}
*/
