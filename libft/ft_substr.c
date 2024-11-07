/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:06:57 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/22 17:00:10 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			s_len;
	size_t			i;
	unsigned char	*dest;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		dest[i] = (unsigned char)s[i + start];
		i++;
	}
	dest[i] = '\0';
	return ((char *)dest);
}
/*
#include <stdio.h>

int	main()
{
	char	*str = "bienoubien";

	printf("%s", ft_substr(str, 4, 4));
}
*/
