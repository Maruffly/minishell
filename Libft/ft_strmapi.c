/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:09 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/23 13:29:38 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len_s;
	char	*dest;

	if (!s || !f)
		return (NULL);
	len_s = ft_strlen(s);
	dest = malloc(len_s + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	dest[len_s] = '\0';
	return (dest);
}
