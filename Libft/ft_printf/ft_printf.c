/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:06:30 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/06/20 15:23:08 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_specifiers(va_list args, const char specifier, int *nb_char)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(args, int), nb_char));
	else if (specifier == 's')
		return (ft_putstr(va_arg(args, char *), nb_char));
	else if (specifier == 'p')
		return (ft_putptr(va_arg(args, unsigned long int), nb_char));
	else if (specifier == '%')
		return (ft_putchar('%', nb_char));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(args, int), nb_char, 0));
	else if (specifier == 'u')
		return (ft_putnbr(va_arg(args, unsigned int), nb_char, 1));
	else if (specifier == 'x')
		return (ft_puthexa(va_arg(args, unsigned int), nb_char, 'x'));
	else if (specifier == 'X')
		return (ft_puthexa(va_arg(args, unsigned int), nb_char, 'X'));
	return ;
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			nb_char;
	int			i;

	if (!str)
		return (-1);
	nb_char = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			++i;
			check_specifiers(args, str[i], &nb_char);
			i++;
		}
		else
			ft_putchar(str[i++], &nb_char);
	}
	va_end(args);
	return (nb_char);
}

/* int main()
{
	unsigned int test_uint = UINT_MAX;
	char	test_char = 'Z';
	char	*test_str = "bienoubien";
	void	*test_ptr = &test_uint;
	int		int_normal = 1995;

	ft_printf("Character: %c;  Int : %i;  Unsigned : %u; proute\n",
		test_char, INT_MAX, (UINT_MAX));
	ft_printf("Pointer: %p\n", test_ptr);
	ft_printf("Signed integer (%%d): %d\n", int_normal);
	ft_printf("Signed integer (%%i): %i\n", INT_MIN);
	ft_printf("Unsigned integer: %u\n", -1);
	ft_printf("Hexadecimal (lowercase): %x\n", test_uint);
	ft_printf("Hexadecimal (uppercase): %X\n", int_normal);
	ft_printf("Percent sign: %%  %z %d\n", test_uint);
	// Test len
	ft_printf("%d\n", ft_printf("Customiz - Wesh alors %p len : ", test_ptr));
	printf("%d\n", printf("Original - Wesh alors %p len : ", test_ptr));

	printf("%d", ft_printf("String %s - len : ", test_str));
	return 0;
} */
