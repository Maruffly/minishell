/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:17:42 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/21 13:59:40 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
	i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main() {
    const char *haystack = "Hello, World!";
    const char *needle = "\0";
    size_t len = 12;

    char *result = strnstr(haystack, needle, len);

    if (result != NULL) {
        printf("Sous-chaîne trouvée : %s\n", result);
    } else {
        printf("Sous-chaîne non trouvée dans 
	les %zu premiers caractères.\n", len);
    }

    return 0;
}
*/
