/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:01:23 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/04 16:34:01 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dest;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dest)
		return (free(dest), NULL);
	ft_strlcpy(dest, s1, (1 + s1_len));
	ft_strlcat(dest, s2, (s1_len + s2_len + 1));
	return (dest);
}
/*
#include <stdio.h>

int	main()
{
	printf("%s", ft_strjoin("bien", "wesh"));
}
*/
