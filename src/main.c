/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/12 15:47:36 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal_value = 0;

int	process_prompt(char *input, t_shell *sh)
{
	t_token	*token_list;
	t_ast	*ast;
	int		status;

	status = lexer(input, &token_list, sh);
	if (status == EXIT_SUCCESS && token_list)
	{
		status = parser(token_list, &ast, sh);
		if (status == EXIT_SUCCESS && ast)
		{
			// status = exec_heredocs();
			//  if (status == EXIT_SUCCESS)
			// 	status = execute();
		}
	}
	return (status);
}

int	launch_shell(t_shell *sh)
{
	char	*input;

	while(1)
	{
		input = read_line(MAIN_PROMPT);
		handle_eof(input, sh);
		if (g_signal_value == SIGINT)
			sh->last_status = 130;
		if (input)
		{
			add_history(input);
			sh->last_status = process_prompt(input, sh);
		}
	}
}

char	*read_line(t_prompt_mode mode)
{
	char		*input;

	g_signal_value = 0;
	input = NULL;
	if (mode == MAIN_PROMPT)
	{
		input = readline(GREEN"Omar&Fred>"RESET);
		set_main_signals();
	}
	else if (mode == HEREDOC_PROMPT)
	{
		set_heredoc_signal();
		input = readline("> ");
		set_main_signals();
	}
	return (input);
}

void	init_shell(t_shell *sh, char **envp)
{
	sh->is_parent = true;
	sh->last_status = EXIT_SUCCESS;
	sh->env = init_envp(envp);
	sh->parsing_error = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;
	int		status;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	set_main_signals();
	init_shell(&sh, envp);
	status = launch_shell(&sh);
	exit_shell(status, &sh);
	return (0);
}
