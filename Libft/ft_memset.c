/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:51:11 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 12:14:17 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    char str[50] = "Thisss is onnnly a  tesssst.";

    printf("Original string: %s\n", str);

    // Use ft_memset to set the first 5 characters to 'x'
    ft_memset(str, 'x', 5);

    printf("Modified string: %s\n", str);

    return 0;
}
*/
