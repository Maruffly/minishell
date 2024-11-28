/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:03:37 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/28 17:35:41 by jmaruffy         ###   ########.fr       */
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

bool	is_separator(t_token_type type)
{
	if (type == PIPE || type == AND || type == OR || type == PAR)
		return (true);
	return (false);
}

bool	is_redirection(t_token_type type)
{
	if (type ==  REDIRECT_IN|| type == REDIRECT_IN ||
		type == APPEND_OUT || type == HEREDOC)
		return (1);
	return (0);
}
