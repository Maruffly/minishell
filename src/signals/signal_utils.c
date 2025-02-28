/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:08:46 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:00:53 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

sig_atomic_t	g_signal_value = 0;

void	sigint_prompt(int signum)
{
	g_signal_value = signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_heredoc(int signum)
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
