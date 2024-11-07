/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:18:17 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/06/20 14:59:45 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int c, int *count_char)
{
	write(1, &c, 1);
	*count_char += 1;
}

void	ft_putstr(char *s, int *count_char)
{
	size_t	i;

	if (!s)
	{
		ft_putstr("(null)", count_char);
		return ;
	}
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i], count_char);
		i++;
	}
}

void	ft_putnbr(long int n, int *count_char, int is_unsigned)
{
	if (n == LONG_MIN)
	{
		write(1, "-9223372036854775808", 20);
		*count_char += 20;
		return ;
	}
	if (n < 0 && !is_unsigned)
	{
		ft_putchar('-', count_char);
		n = -n;
	}
	if (n >= 0 && n <= 9)
		ft_putchar('0' + n, count_char);
	else
	{
		ft_putnbr(n / 10, count_char, is_unsigned);
		ft_putchar(n % 10 + '0', count_char);
	}
}

void	ft_puthexa(unsigned long long int n, int *count_char, char specifier)
{
	char	*base;

	if (specifier == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n <= 15)
		ft_putchar(base[0 + n], count_char);
	if (n > 15)
	{
		ft_puthexa(n / 16, count_char, specifier);
		ft_putchar(base[n % 16], count_char);
	}
}

void	ft_putptr(unsigned long int ptr, int *count_char)
{
	if (ptr == 0)
		return (ft_putstr("(nil)", count_char));
	ft_putstr("0x", count_char);
	ft_puthexa(ptr, count_char, 'x');
}
