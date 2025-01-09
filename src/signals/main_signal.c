/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:57 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/09 17:20:00 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libraries.h"
#include "../../includes/structures.h"

void	handle_eof(char *input, t_shell *sh)
{
	if (!input)
		exit_shell(sh->last_status, sh);
}

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	set_heredoc_signals(void)
{
	
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


void	set_signal_handler(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(signum, &sa, NULL);
}

void	set_signal_child_process(void)
{
	set_signal_handler(SIGINT, SIG_DFL);
	set_signal_handler(SIGQUIT, SIG_DFL);
}

// void	handle_signal(int signum, void (*handler)(int))
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = handler;
// 	sa.sa_flags = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(signum, &sa, NULL);
// }

// void	sigint_handler(int signum)
// {
// 	(void)signum;
// 	g_signal_value = SIGINT;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	sigquit_handler(int signum)
// {
// 	(void)signum;
// 	write(1, "\r", 1);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	set_main_signals(void)
// {
// 	handle_signal(SIGINT, sigint_handler);
// 	handle_signal(SIGQUIT, sigquit_handler);
// }

// void	set_heredoc_signal(void)
// {
// 	handle_signal(SIGINT, sigint_handler);
// 	handle_signal(SIGQUIT, SIG_IGN);
// }
