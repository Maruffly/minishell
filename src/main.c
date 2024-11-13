/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/13 18:22:18 by jbmy             ###   ########.fr       */
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

/* void	init_token_type(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->command[++i])
	{
		if (is_builtin(cmd->command[i]) || )
			
	}
} */

void	read_line(t_command *cmd)
{
	char	*input;

	while (1)
	{
		input = readline("Omar&Fred> ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			cmd->value = ft_strdup(input);
			if (!cmd->value)
			{
				perror("Fail to copy input");
				free(input);
				continue ;
			}
			cmd->command = malloc(sizeof(char *) * (ft_strlen(input) + 1));
			if (!cmd->command)
			{
				perror("Fail to alloc memory for commands");
				free(input);
				continue ;
			}
			init_command_array(cmd, input);
			break ;
		}
		else
		{
			free(input);
			continue;
		}

	}
}

int	main()
{
	t_command	cmd;

	signal(SIGINT, signal_handler);
	read_line(&cmd);
}
