/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:29:18 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/30 15:00:42 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char **text)
{
	int				bytes_read;
	char			*tmp;

	bytes_read = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!*text)
		*text = ft_strdup("");
	while (bytes_read && !ft_strchr(*text, '\n'))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*text);
			*text = NULL;
			return (free(tmp), NULL);
		}
		tmp[bytes_read] = '\0';
		*text = ft_strjoin(*text, tmp);
	}
	free (tmp);
	return (NULL);
}

char	*extract_line(char **text)
{
	char	*buffer;
	char	*line;

	if (!ft_strchr(*text, '\n'))
	{
		line = ft_strdup(*text);
		free (*text);
		*text = NULL;
	}
	else
	{
		line = ft_substr(*text, 0, ft_strchr(*text, '\n') - *text + 1);
		buffer = ft_strdup(ft_strchr(*text, '\n') + 1);
		free(*text);
		*text = buffer;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*readed;

	readed = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(fd, &buffer);
	if (buffer && buffer[0] != 0)
		readed = extract_line(&buffer);
	if (buffer && buffer[0] == 0)
	{
		free(buffer);
		buffer = NULL;
	}
	return (readed);
}

int	main(void)
{
	int		fd;
	char	*next_line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("error file");
		return (1);
	}
	next_line = get_next_line(fd);
	while ((next_line != NULL))
	{
		printf("LINE = %s\n", next_line);
		free(next_line);
		next_line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
