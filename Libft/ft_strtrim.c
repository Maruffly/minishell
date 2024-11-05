/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:18:39 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/05/30 15:28:45 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	size_t	dest_len;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	dest_len = end - start;
	dest = malloc(sizeof(char) * dest_len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1 + start, dest_len + 1);
	return (dest);
}
/*
int main(void)
{
    char *str;
    char *set;
    char *result;

    str = "  bon jouarrr  ";
    set = " ";
    result = ft_strtrim(str, set);
    printf("Original string: '%s'\n", str);
    printf("Set to trim: '%s'\n", set);
    printf("Trimmed string: '%s'\n", result);
    free(result);

    str = "xxyouuu houuuxx";
    set = "x";
    result = ft_strtrim(str, set);
    printf("Original string: '%s'\n", str);
    printf("Set to trim: '%s'\n", set);
    printf("Trimmed string: '%s'\n", result);
    free(result);

    str = "abcweeesh alorsdabc";
    set = "abc";
    result = ft_strtrim(str, set);
    printf("Original string: '%s'\n", str);
    printf("Set to trim: '%s'\n", set);
    printf("Trimmed string: '%s'\n", result);
    free(result);

    str = "yarrfrrr";
    set = "";
    result = ft_strtrim(str, set);
    printf("Original string: '%s'\n", str);
    printf("Set to trim: '%s'\n", set);
    printf("Trimmed string: '%s'\n", result);
    free(result);

    str = "";
    set = " ";
    result = ft_strtrim(str, set);
    printf("Original string: '%s'\n", str);
    printf("Set to trim: '%s'\n", set);
    printf("Trimmed string: '%s'\n", result);
    free(result);

    return 0;
}
*/
