/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:02 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/30 15:56:20 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	free_heredoc(t_heredoc *hdoc)
{
	if (!hdoc)
		return ;
	free(hdoc->limiter);
	free(hdoc);
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
