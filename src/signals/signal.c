/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:57 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/29 14:38:07 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	handle_eof(char *input, t_shell *sh)
{
	if (!input)
		exit_shell(sh->last_status, sh);
}

void	set_child_signals(void)
{
	set_signal(SIGINT, SIG_DFL);
	set_signal(SIGQUIT, SIG_DFL);
}

void	sigint_handler(int signum)
{
	(void)signum;
	g_signal_value = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal(int signum, void (*handler)(int))
 {
 	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(signum, &sa, NULL);
}
