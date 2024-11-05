/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:42 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 10:40:52 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_char(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*dest;
	size_t		count;
	long int	num;

	num = n;
	count = count_char(n);
	if (n < 0)
		count++;
	dest = malloc(sizeof(char) * (count + 1));
	if (dest == NULL)
		return (NULL);
	dest[count] = '\0';
	if (n < 0)
		num = -num;
	while (count > 0)
	{
		dest[--count] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}

/*
#include <stdio.h>
#include <limits.h>

int main()
{
	int	num[] = {0, -12345, 12345, INT_MIN, INT_MAX};
	size_t	num_count = sizeof(num) / sizeof(num[0]);

	for (size_t i = 0; i < num_count; i++) 
	{
		char *str = ft_itoa(num[i]);
		if (str != NULL)
		{
			printf("Integer: %d -> String: %s\n", num[i], str);
			free(str);
        	}
		else
			printf("Failed to alloc mem: %d\n", num[i]);
    	}
	return 0;
}
*/
