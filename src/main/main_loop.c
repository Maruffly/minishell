/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:03:58 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 20:45:48 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_prompt(t_shell *sh)
{
	while (sh->in_main_process && sh->temporary_files)
	{
		if (unlink(sh->temporary_files->content) == -1)
			report_errno("unlink", sh);
		sh->temporary_files = sh->temporary_files->next;
	}
	ft_lstclear(&(sh->allocated_pointers[PROMPT]), free);
	sh->parsing_error = NULL;
}

int	main_loop(t_shell *sh)
{
	char	*user_input;

	while (42)
	{
		g_signal_value = 0;
		user_input = process_prompt(MAIN_PROMPT);
		if (g_signal_value == SIGINT)
			sh->last_status = 130;
		if (!user_input)
			exit_shell(sh->last_status, sh);
		track_alloc(user_input, PROMPT, sh);
		if (ft_strlen(user_input) > 0)
		{
			add_history(user_input);
			sh->last_status = process_prompt(user_input, sh);
		}
		clear_prompt(sh);
	}
	return (sh->last_status);
}

char	*prompt_listener(t_prompt_mode mode)
{
	char	*user_input;

	g_signal_value = 0;
	user_input = NULL;
	rl_replace_line("", 0);
	rl_on_new_line();
	if (mode == MAIN_PROMPT)
	{
		set_signal_prompt();
		user_input = readline("\x1b[32mminishell$ \x1b[0m");
		set_signal_main_process();
	}
	else if (mode == HEREDOC_PROMPT)
	{
		set_signal_heredoc();
		user_input = readline("> ");
		set_signal_main_process();
	}
	return (user_input);
}
