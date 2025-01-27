/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:58:12 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/27 12:24:52 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

static void	print_exit_code(int	exit_code)
{
	printf("%d\n", exit_code);
}

static void	set_exit_code(int *exit_code, int code)
{
	*exit_code = code;
	print_exit_code(*exit_code);
}

void	handle_exit_status(char *input, int *exit_code)
{
	if (ft_strcmp(input, "$?") == 0)
		print_exit_code(*exit_code);
	else if (ft_strcmp(input, "Ctrl+C") == 0)
		set_exit_code(exit_code, 130);
	else if (ft_strcmp(input, "Ctrl+\\") == 0)
		set_exit_code(exit_code, 131);
	else if (ft_strcmp(input, "command_not_found") == 0)
		set_exit_code(exit_code, 127);
	else if (ft_strcmp(input, "permission_denied") == 0)
		set_exit_code(exit_code, 126);
	else
		set_exit_code(exit_code, 1);
}

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
