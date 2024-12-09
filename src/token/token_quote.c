/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:35:49 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/09 13:49:58 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	in_single_quote(char *line, int idx)
{
	int	in_single_quote;
	int	i;

	in_single_quote = 0;
	i = 0;
	while (line[i] && i < idx)
	{
		if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
			in_single_quote = !in_single_quote;
		i++;
	}
	return (in_single_quote);
}

int	in_double_quote(char *line, int idx)
{
	int	in_double_quote;
	int	i;

	in_double_quote = 0;
	i = 0;
	while (line[i] && i < idx)
	{
		if (line[i] == '"' && (i == 0 || line[i - 1] != '\\'))
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_double_quote);
}
