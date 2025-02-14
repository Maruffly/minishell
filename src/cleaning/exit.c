/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:58:12 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/14 17:18:37 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

void	*syntax_error(char *unexpected_token, t_shell *sh)
{
	if (sh->parsing_error)
		return (NULL);
	sh->parsing_error = unexpected_token;
	ft_putstr_fd("Omar&Fred: syntax error near unexpected token `",
		STDERR_FILENO);
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
	sh->parsing_error = NULL;
	return (2);
}

void	exit_shell(int exit_status, t_shell *sh)
{
	if (sh)
	{
		if (sh->is_parent && isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDERR_FILENO);
		if (sh->env)
			ft_lstclear_env(&sh->env, free_env_list);
	}
	rl_clear_history();
	exit(exit_status);
}
