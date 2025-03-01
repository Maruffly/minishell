/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:03:58 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 11:24:35 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_prompt(t_prompt_mode mode)
{
	char	*user_input;

	g_signal_value = 0;
	user_input = NULL;
	rl_replace_line("", 0);
	rl_on_new_line();
	if (mode == MAIN_PROMPT)
	{
		set_signal_prompt();
		user_input = readline(GREEN"Omar&Fred > "RESET);
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

int	parse_and_exec(char *user_input, t_shell *sh)
{
	t_list	*token_list;
	t_ast	*ast;
	int		status;

	status = lexer(user_input, &token_list, sh);
	if (status == EXIT_SUCCESS && token_list)
	{
		status = parser(token_list, &ast, sh);
		if (status == EXIT_SUCCESS && ast)
		{
			status = execute_heredocs(ast, sh);
			if (status == EXIT_SUCCESS)
				status = execute(ast, O_RETURN, sh);
		}
	}
	return (status);
}

int	main_loop(t_shell *sh)
{
	char	*user_input;

	while (42)
	{
		g_signal_value = 0;
		user_input = get_prompt(MAIN_PROMPT);
		if (g_signal_value == SIGINT)
			sh->last_status = 130;
		if (!user_input)
			exit_shell(sh->last_status, sh);
		track_alloc(user_input, PROMPT, sh);
		if (ft_strlen(user_input) > 0)
		{
			add_history(user_input);
			sh->last_status = parse_and_exec(user_input, sh);
		}
		clear_prompt(sh);
	}
	return (sh->last_status);
}
