/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:59:14 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/29 16:28:07 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}
/*
int main(void) 
{
    const char *str1 = "";
    const char *str2 = "   -456";
    const char *str3 = "+789";
    const char *str4 = "42 is the answer";
    const char *str5 = "   2147483647";
    const char *str6 = "   -2147483648";
    const char *str7 = "    0";
    const char *str8 = "  +000123";
    
    printf("String: '%s' -> Integer: %d\n", str1, ft_atoi(str1));
    printf("String: '%s' -> Integer: %d\n", str2, ft_atoi(str2));
    printf("String: '%s' -> Integer: %d\n", str3, ft_atoi(str3));
    printf("String: '%s' -> Integer: %d\n", str4, ft_atoi(str4));
    printf("String: '%s' -> Integer: %d\n", str5, ft_atoi(str5));
    printf("String: '%s' -> Integer: %d\n", str6, ft_atoi(str6));
    printf("String: '%s' -> Integer: %d\n", str7, ft_atoi(str7));
    printf("String: '%s' -> Integer: %d\n", str8, ft_atoi(str8));
    
    return 0;
}
*/
