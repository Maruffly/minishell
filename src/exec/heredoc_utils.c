/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:02 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/30 15:23:46 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	free_heredoc(t_heredoc *hdoc, t_expand *exp)
{
	(void)exp;
	if (!hdoc)
		return ;
	free(hdoc->limiter);
	free(hdoc);
}

int	is_quoted(char *str)
{
	size_t	len;
	char	quote;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	quote = str[0];
	if ((quote == '\'' || quote == '\"') && str[len - 1] == quote)
		return (1);
	return (0);
}

void	remove_quotes(char *str)
{
	size_t	len;
	size_t	i;

	if (!str || !*str)
		return ;

	len = ft_strlen(str);
	if (len < 2)
		return ;
	if (str[0] == '\'' || str[0] == '\"')
	{
		i = 0;
		while (i < len - 1)
		{
			str[i] = str[i + 1];
			i++;
		}
		str[len - 2] = '\0';
	}
}

int heredoc_eof_handler(t_heredoc *hdoc)
{
	static int	line_count = 1;
	char		*line_str;

	line_str = ft_itoa(line_count++);
	if (!line_str)
		return (EXIT_FAILURE);
	ft_putstr_fd("\nOmar&Fred: warning: here-document at line ", 2);
	ft_putstr_fd(line_str, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(hdoc->limiter, 2);
	ft_putstr_fd("')\n", 2);
	free(line_str);
	return (EXIT_SUCCESS);
}

bool	write_to_pipe(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1
		|| write(fd, "\n", 1) == -1)
		return (false);
	return (true);
}
