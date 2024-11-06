/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:43:39 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/22 14:07:13 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			ch;
	char			*last_occ;

	last_occ = NULL;
	ch = (char)c;
	while (*str)
	{
		if (*str == ch)
			last_occ = (char *)str;
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (last_occ);
}
