/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/09 14:09:41 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal_value = 0;

int	process_prompt(char *input, t_shell *sh)
{
	t_token	*token_list;
	/* t_ast	*ast; */
	int		status;

	status = lexer(input, &token_list, sh);
	/* if (status == EXIT_SUCCESS && token_list)
	{
		status = parser();
		if (status == EXIT_SUCCESS && ast)
		{
			status = exec_heredocs();
			if (status == EXIT_SUCCESS)
				status = execute();
		}
	} */
	return (status);
}

int	launch_shell(t_shell *sh)
{
	char	*input;

	while(1)
	{
		input = read_line(MAIN_PROMPT);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		if (g_signal_value == SIGINT)
			sh->last_status = 130;
		if (!input)
			exit_shell(sh->last_status, sh);
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

	}
	else if (mode == HEREDOC_PROMPT)
	{
		input = readline("> ");

	}
	return (input);
}

void	init_shell(t_shell *sh, char **envp)
{
	sh->is_parent = true;
	sh->last_status = EXIT_SUCCESS;
	sh->env = envp_to_list(envp);
	sh->parsing_error = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;
	int		status;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	init_shell(&sh, envp);
	status = launch_shell(&sh);
	exit_shell(status, &sh);
	return (0);
}
