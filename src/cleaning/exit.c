/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:58:12 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/30 14:36:57 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

void	*syntax_error(char *unexpected_token, t_shell *sh)
{
	ft_putstr_fd("Omar&Fred: syntax error near unexpected token `", STDERR_FILENO);
	if (!unexpected_token || !!*unexpected_token)
		ft_putstr_fd("newline'", STDERR_FILENO);
	else
		ft_putstr_fd(unexpected_token, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	sh->last_status = 2;
	return (NULL);
}


int	report_syntax_error(t_shell *sh)
{
	/* report_error("syntax error near unexpected token `",
		sh->parsing_error, "'", sh); */
	sh->parsing_error = NULL;
	return (2);
}
