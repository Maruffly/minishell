/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:18 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/04 16:37:03 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char sep)
{
	int	counter;
	int	flag;
	int	i;

	counter = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != sep && flag == 0)
		{
			flag = 1;
			counter++;
		}
		else if (s[i] == sep)
			flag = 0;
		i++;
	}
	return (counter);
}

static void	free_substr(char **sub_str, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		if (sub_str[i])
			free(sub_str[i]);
		i++;
	}
	free(sub_str);
}

static char	*word_cpy(char const *str, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i++] = str[start++];
	}
	word[i] = '\0';
	return (word);
}

static char	**parse_s(char const *s, char c, char **sub_str)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			sub_str[j] = word_cpy(s, start, i);
			if (!sub_str[j++])
			{
				free_substr(sub_str, j - 1);
				return (NULL);
			}
		}
	}
	sub_str[j] = NULL;
	return (sub_str);
}

char	**ft_split(char *s, char c)
{
	char	**sub_str;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	sub_str = malloc(sizeof(char *) * (word_count + 1));
	if (!sub_str)
		return (NULL);
	if (!parse_s(s, c, sub_str))
		return (NULL);
	return (sub_str);
}
