/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:02 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/09 16:03:01 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void free_heredoc(t_heredoc *hdoc)
{
	if (!hdoc)
		return ;
	free(hdoc->limiter);
	free(hdoc);
}

int is_quoted(char *str)
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

void remove_quotes(char *str)
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

static int	is_valid_heredoc_delimiter(char *unquoted)
{
	size_t i;

	if (!unquoted || !ft_strlen(unquoted))
		return (0);

	i = 0;
	while (unquoted[i])
	{
		if (!ft_isprint(unquoted[i]))
			return (0);
		
		if (ft_strchr(" \t\n\v\f\r", unquoted[i]))
			return (0);
			
		i++;
	}
	return (1);
}

int is_valid_delimiter(char *delimiter)
{
	size_t	i;
	char	*unquoted;
	int 	valid;

	if (!delimiter || !ft_strlen(delimiter))
		return (0);
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
	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] < 32 || delimiter[i] > 126 || ft_strchr("<>|&;()", delimiter[i]))
			return (0);
		i++;
	}
	return (1);
}

/* t_expand	*get_var_name(char *str, t_expand *exp, t_shell *sh)
{
	size_t	i;
	t_expand	*var;

	exp->buf_size = 0;
	if (!str || !*str)
		return (var);
	if (*str == '?')
	{
		var->buf = ft_substr(str, 0, 1);
		var->buf_size = 1;
		return (var);
	}
	var->buf = get_valid_name(str, exp, sh);
	return (var->buf);
} */