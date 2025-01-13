/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:31 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal_value = 0;

int	process_prompt(char *input, t_shell *sh)
{
	t_ast	*ast;
	int		process;
	t_token	*token_lst;

	process = lexer(input, &token_lst, sh);
	if (process == EXIT_SUCCESS && token_lst)
	{
		process = parser(token_lst, &ast, sh);
		/* print_ast(ast); */
		/* return (0); */
		if (process == EXIT_SUCCESS && ast)
		{
			process = execute_heredoc(ast, sh);
			//  if (process == EXIT_SUCCESS)
				// process = execute();
		}
	}
	return (process);
}

int	launch_shell(t_shell *sh)
{
	char	*input;

	while(1)
	{
		g_signal_value = 0;
		input = read_line(MAIN_PROMPT);
		handle_eof(input, sh);
		if (g_signal_value == SIGINT)
			sh->last_status = 130;
		if (input)
		{
			add_history(input);
			sh->last_status = process_prompt(input, sh);
			break ;
		}
		break ;
	}
	return (0);
}

char	*read_line(t_prompt_mode mode)
{
	char	*input;

	g_signal_value = 0; // reinitialise le signal global
	set_signal(SIGINT, SIG_IGN); // ignore SIGINT et SIGQUIT au lancement
	set_signal(SIGQUIT, SIG_IGN);
	if (mode == MAIN_PROMPT)
	{
		set_signal(SIGINT, sigint_handler);
		input = readline(GREEN"Omar&Fred > "RESET);
	}
	else if (mode == HEREDOC_PROMPT)
	{
		set_signal(SIGINT, heredoc_sigint_handler);
		input = readline("> ");
	}
	else
		input = NULL;
	set_signal(SIGINT, SIG_DFL); // restaure les signaux apres lecture de l'input
	set_signal(SIGQUIT, SIG_DFL);
	return (input);
}


// char	*read_line(t_prompt_mode mode)
// {
// 	char		*input;

// 	input = NULL;
// 	g_signal_value = 0;
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	if (mode == MAIN_PROMPT)
// 	{
// 		// input = "ls -l > output | cat output && (echo bonjour)";
// 		input = readline(GREEN"Omar&Fred>"RESET);
// 		set_main_signals();
// 	}
// 	else if (mode == HEREDOC_PROMPT)
// 	{
// 		set_heredoc_signal();
// 		input = readline("> ");
// 		set_main_signals();
// 	}
// 	return (input);
// }

void	init_shell(t_shell *sh, char **envp)
{
	sh->is_parent = true;
	sh->prompt_mode = MAIN_PROMPT;
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
	// set_main_signals();
	init_shell(&sh, envp);
	status = launch_shell(&sh);
	exit_shell(status, &sh);
	return (0);
}

/*
Logical operation: &&
Left:
	Pipeline:
			Left:
				Redirection: > to file 'output'
							Child of redirection:
												Command: ls -l ls -l
			Right:
				Command: cat output cat output
Right:
	Subshell:
			Command: echho bonjour echho bonjour
*/
