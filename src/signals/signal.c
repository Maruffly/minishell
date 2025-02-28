/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:57 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 21:19:03 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_signal_handler(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(signum, &sa, NULL);
}

void	set_signal_prompt(void)
{
	set_signal_handler(SIGINT, sigint_prompt);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

void	set_signal_main_process(void)
{
	set_signal_handler(SIGINT, SIG_IGN);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

void	set_signal_child_process(void)
{
	set_signal_handler(SIGINT, SIG_DFL);
	set_signal_handler(SIGQUIT, SIG_DFL);
}

void	set_signal_heredoc(void)
{
	set_signal_handler(SIGINT, sigint_heredoc);
	set_signal_handler(SIGQUIT, SIG_IGN);
}
