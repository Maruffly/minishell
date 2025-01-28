/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:38:50 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/28 11:14:21 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

bool	is_delimiter(char *line, char *delimiter)
{
	return (ft_strcmp(line, delimiter) == 0);
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
