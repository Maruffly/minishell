/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:27:46 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 11:40:07 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(char *context, char *description, int exit_status,
	t_shell *sh)
{
	ft_putstr_fd("Omar&Fred ", STDERR_FILENO);
	ft_putstr_fd(description, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(context, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit_shell(exit_status, sh);
}

void	error_handler(char *context, int errnum, t_shell *sh)
{
	error(context, strerror(errnum), EXIT_FAILURE, sh);
}

int	report_errno(char *context, t_shell *sh)
{
	(void)sh;
	ft_putstr_fd("Omar&Fred ", 2);
	perror(context);
	return (EXIT_FAILURE);
}

int	report_error(char *context, char *element, char *description, t_shell *sh)
{
	(void)sh;
	ft_putstr_fd("Omar&Fred ", STDERR_FILENO);
	ft_putstr_fd(context, STDERR_FILENO);
	if (element)
		ft_putstr_fd(element, STDERR_FILENO);
	ft_putstr_fd(description, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	report_syntax_error(t_shell *sh)
{
	report_error("syntax error near unexpected token `",
		sh->parsing_error, "'", sh);
	sh->parsing_error = NULL;
	return (2);
}
