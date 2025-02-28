/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:27:46 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 21:02:56 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(const char *context, char *description, int exit_status,
	t_shell *sh)
{
	ft_write_fd("Omar&Fred ", STDERR_FILENO);
	ft_write_fd(description, STDERR_FILENO);
	ft_write_fd(": ", STDERR_FILENO);
	ft_write_fd(context, STDERR_FILENO);
	ft_write_fd("\n", STDERR_FILENO);
	quit_shell(exit_status, sh);
}

void	error_handler(const char *context, int errnum, t_shell *sh)
{
	error(context, strerror(errnum), EXIT_FAILURE, sh);
}

int	report_errno(char *context, t_shell *sh)
{
	write_s("Omar&Fred ", 2, sh);
	perror(context);
	return (EXIT_FAILURE);
}

int	report_error(char *context, char *element, char *description, t_shell *sh)
{
	write_s("Omar&Fred ", STDERR_FILENO, sh);
	write_s(context, STDERR_FILENO, sh);
	if (element)
		write_s(element, STDERR_FILENO, sh);
	write_s(description, STDERR_FILENO, sh);
	write_s("\n", STDERR_FILENO, sh);
	return (EXIT_FAILURE);
}

int	report_syntax_error(t_shell *sh)
{
	report_error("syntax error near unexpected token `",
		sh->parsing_error, "'", sh);
	sh->parsing_error = NULL;
	return (2);
}
