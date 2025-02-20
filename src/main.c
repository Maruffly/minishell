/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/20 16:29:56 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_prompt(char *input, t_shell *sh)
{
	t_ast		*ast;
	int			process;
	t_token		*token_lst;

	ast = NULL;
	process = lexer(input, &token_lst, sh);
	if (process != EXIT_SUCCESS || !token_lst)
		return (process);
	process = parser(token_lst, &ast, sh);
	if (process != EXIT_SUCCESS || !ast)
		return (handle_parsing_error(sh, token_lst));
	process = handle_heredoc_ast(ast, sh);
	if (process != EXIT_SUCCESS)
	{
		free_ast(ast);
		free_token_list(token_lst);
		return (process);
	}
	process = execute(ast, KEEP_RUNNING, sh);
	close_heredoc_fds(ast);
	free_token_list(token_lst);
	free_ast(ast);
	if (sh->must_exit == true)
		exit(sh->last_status);
	return (process);
}

char	*read_line(t_prompt_mode mode)
{
	char	*input;

	g_signal_value = 0;
	input = NULL;
	rl_replace_line("", 0);
	rl_on_new_line();
	if (mode == MAIN_PROMPT)
	{
		set_main_signals();
		input = readline(GREEN"Omar&Fred > "RESET);
		main_signal();
	}
	else if (mode == HEREDOC_PROMPT)
	{
		set_heredoc_signals();
		input = readline("> ");
		set_main_signals();
	}
	else
		input = NULL;
	return (input);
}

int	launch_shell(t_shell *sh)
{
	char	*input;
	int		process_status;

	while (42)
	{
		g_signal_value = 0;
		input = read_line(MAIN_PROMPT);
		if (g_signal_value == SIGINT)
			sh->last_status = 130;
		handle_eof(input, sh);
		if (*input == ':' || *input == '!')
		{
			sh->last_status = 1;
			free(input);
			continue ;
		}
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			process_status = process_prompt(input, sh);
			if (sh->last_status == 0)
				sh->last_status = process_status;
			sh->parsing_error = NULL;
		}
		free(input);
	}
	return (0);
}

void	shell_level(t_shell *sh)
{
	t_env_list	*shlvl_var;
	int			new_value;
	char		*new_value_str;

	shlvl_var = find_env_node(sh->env, "SHLVL");
	if (!shlvl_var)
		return (add_env_node(sh->env, "SHLVL", "1"));
	new_value = ft_atoi(shlvl_var->var_value) + 1;
	new_value_str = ft_itoa(new_value);
	if (new_value < 0)
		update_env_node(sh->env, "SHLVL", "0");
	else if (new_value > 1000)
	{
		error("warning: shell level", "("
			") too high, resetting to 1", 2, sh);
		update_env_node(sh->env, "SHLVL", "1");
	}
	else
		update_env_node(sh->env, "SHLVL", new_value_str);
	free(new_value_str);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;
	int		status;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	main_signal();
	init_shell(&sh, envp);
	status = launch_shell(&sh);
	exit_shell(status, &sh);
	return (0);
}
