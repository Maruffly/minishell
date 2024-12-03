/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:37 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/03 14:19:54 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/token.h"

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

bool	is_redirection(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT ||
			type == APPEND_OUT || type == HEREDOC);
}
