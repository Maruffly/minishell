/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:57 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/10 15:30:10 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_eof(char *input, t_shell *sh)
{
	if (!input)
		exit_shell(sh->last_status, sh);
}

void	heredoc_sigint_handler(int signum)
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

void	set_signal_prompt(void)
{
	int	signum;

	(void)signum;
	set_signal(SIGINT, sigint_handler);
	set_signal(SIGQUIT, SIG_IGN);
}

void	set_signal_main_process(void)
{
	set_signal(SIGINT, SIG_IGN);
	set_signal(SIGQUIT, SIG_IGN);
}

void	set_signal_child_process(void)
{
	set_signal(SIGINT, SIG_DFL);
	set_signal(SIGQUIT, SIG_DFL);
}

void	set_signal_heredoc(void)
{
	printf("Configuring signals for heredoc\n");
	set_signal(SIGINT, heredoc_sigint_handler);
	set_signal(SIGQUIT, SIG_IGN);
}