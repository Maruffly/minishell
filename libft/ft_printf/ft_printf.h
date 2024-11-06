/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:06:32 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/06/20 15:24:13 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(int c, int *count_char);
void	ft_putstr(char *s, int *count_char);
void	ft_putnbr(long int nb, int *count_char, int is_unsigned);
void	ft_puthexa(unsigned long long int n, int *count_char, char specifier);
void	ft_putptr(unsigned long int ptr, int *count);

#endif
