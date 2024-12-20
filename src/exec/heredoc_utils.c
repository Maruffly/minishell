/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:02 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/20 15:58:34 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int is_quoted(char *str)
{
	size_t	len;
	char	quote;

	if (!str || !*str)
		return (0);

	len = ft_strlen(str);
	if (len < 2)
		return (0);

	// Vérifie si la string commence et finit par le même type de quote
	quote = str[0];
	if ((quote == '\'' || quote == '\"') && str[len - 1] == quote)
		return (1);

	return (0);
}

// Enlève les quotes au début et à la fin d'une chaîne
void remove_quotes(char *str)
{
	size_t	len;
	size_t	i;

	if (!str || !*str)
		return ;

	len = ft_strlen(str);
	if (len < 2)
		return ;

	// Si la chaîne commence par une quote
	if (str[0] == '\'' || str[0] == '\"')
	{
		// Décale tous les caractères vers la gauche
		i = 0;
		while (i < len - 1)
		{
			str[i] = str[i + 1];
			i++;
		}
		// Remplace la dernière quote par '\0'
		str[len - 2] = '\0';
	}
}

int heredoc_eof_handler(t_heredoc *hdoc)
{
	static int	line_count;
	char		*line_str;

	line_count = 1;
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

int is_valid_heredoc_delimiter(char *delimiter)
{
	size_t	i;
	char	*unquoted;
	int 	valid;

	if (!delimiter)
		return (0);

	// Si le délimiteur est entre quotes, on vérifie la version sans quotes
	if (is_quoted(delimiter))
	{
		unquoted = ft_strdup(delimiter);
		if (!unquoted)
			return (0);
		remove_quotes(unquoted);
		valid = is_valid_heredoc_delimiter(unquoted);
		free(unquoted);
		return (valid);
	}

	// Un délimiteur ne peut pas être vide
	if (ft_strlen(delimiter) == 0)
		return (0);

	// Vérifie chaque caractère du délimiteur
	i = 0;
	while (delimiter[i])
	{
		// Les caractères de contrôle ne sont pas autorisés
		if (delimiter[i] < 32 || delimiter[i] > 126)
			return (0);
		// Les caractères spéciaux ne sont pas autorisés sans quotes
		if (ft_strchr("<>|&;()", delimiter[i]))
			return (0);
		i++;
	}
	return (1);
}
