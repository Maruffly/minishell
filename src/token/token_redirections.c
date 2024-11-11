/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:37 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/11 17:23:33 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parsing.h"
#include "../includes/builtins.h"
#include "../includes/minishell.h"

int	is_heredoc(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (1);
	return (0);
}

int	is_input_chevrons(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] != '<')
		return (1);
	return (0);
}

int	is_output_chevrons(char *line, int i)
{
	if (line[i] == '>' && line[i + 1] != '>')
		return (1);
	return (0);
}

int	is_append_chevrons(char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>')
		return (1);
	return (0);
}

int	is_redirection(char *line, int i)
{
	if (is_heredoc(line, i) || is_input_chevrons(line, i) ||
		is_output_chevrons(line, i) || is_append_chevrons(line, i))
		return (1);
	return (0);
}
