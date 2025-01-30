/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:43:53 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/30 15:03:46 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buffer[MAX_FD];
	char		*readed;

	readed = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	read_line(fd, &buffer[fd]);
	if (buffer[fd] && buffer[fd][0] != 0)
		readed = extract_line(&buffer[fd]);
	if (buffer[fd] && buffer[fd][0] == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (readed);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	char	*next_line;
	char	*line2;
	char	*line3;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd == -1 || fd2 == -1)
	{
		printf("error file");
		return (1);
	}
	while (((next_line = get_next_line(fd)) != NULL)
		&& ((line2 = get_next_line(fd2)) != NULL) && (line3 = get_next_line(fd2)))
	{
		printf("LINE = %s\n LINE2 = %s\n LINE3 = %s\n", next_line, line2, line3);
		free(next_line);
		free(line2);
		free(line3);
	}
	close(fd);
	close(fd2);
	return (0);
}
