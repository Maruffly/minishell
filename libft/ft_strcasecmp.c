/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:23:45 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/05 11:29:56 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcasecmp(char *s1, char *s2)
{
	char	c1;
	char	c2;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (*s1 || *s2)
	{
		c1 = ft_tolower(*s1);
		c2 = ft_tolower(*s2);
		if (c1 != c2)
			return ((int)c1 - (int)c2);
		if (*s1)
			s1++;
		if (*s2)
			s2++;
	}
	return (0);
}
