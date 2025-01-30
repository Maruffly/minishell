/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:08:46 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/30 15:24:22 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_sigint_handler(int signum)
{
	struct termios	orig_termios;
	struct termios	new_termios;

	g_signal_value = signum;
	tcgetattr(STDIN_FILENO, &orig_termios);
	tcgetattr(STDIN_FILENO, &new_termios);
	new_termios.c_lflag &= (tcflag_t)(~(ICANON | ECHO));
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void	set_heredoc_signals(void)
{
	set_signal(SIGINT, heredoc_sigint_handler);
	set_signal(SIGQUIT, SIG_IGN);
}

static void	sigint_handler(int signum)
{
	(void)signum;
	g_signal_value = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

void	set_main_signals(void)
{
	set_signal(SIGINT, sigint_handler);
	set_signal(SIGQUIT, sigquit_handler);
}
