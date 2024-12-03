/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/03 17:29:07 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		sigint_handler();
}


void	read_line(t_command **cmd, t_env_list *env_list, int exit_status)
{
	char		*input;

	input = readline("Omar&Fred> ");
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		free_env_list(env_list);
		exit(0);
	}
	if (is_empty_line(input))
	{
		free(input);
		*cmd = NULL;
		return ;
	}
	add_history(input);
	*cmd = parse_input(input, env_list, exit_status);
	if (!*cmd)
	{
		perror("Fail to parse input\n");
		*cmd = NULL;
	}
	free(input);
}


// void	read_line(t_command **cmd, t_env_list *env_list, int exit_status)
// {
// 	char		*input;

// 	input = readline("Omar&Fred> ");
// 	if (!input)
// 	{
// 		ft_putstr_fd("exit\n", 1);
// 		free_env_list(env_list);
// 		exit(0);
// 	}
// 	add_history(input);
// 	*cmd = parse_input(input, env_list, exit_status);
// 	if (!*cmd)
// 	{
// 		perror("Fail to parse input\n");
// 		*cmd = NULL;
// 	}
// 	free(input);
// }

int	main(int ac, char **av, char **envp)
{
	t_command	*cmd;
	t_env_list	*env;

	(void)ac;
	(void)av;
	env = envp_to_list(envp);
	cmd = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		read_line(&cmd, env, 0);
		if (!cmd)
			continue ;
		execute_pipeline(cmd, env);
		free_cmd_list(cmd);
		cmd = NULL;
	}
	free_env_list(env);
	return (0);
}
