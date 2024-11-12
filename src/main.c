/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 18:08:19 by jmaruffy         ###   ########.fr       */
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

void	read_line(t_command *cmd)
{
	char	*input;
	int		i;

	while (1)
	{
		input = readline("Omar&Fred> ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			cmd->value = ft_strdup(input);
			cmd->command = ft_split(input, ' ');
			if (!cmd->command)
			{
				perror("Fail to split");
				free(input);
				continue ;
			}
			i = -1;
			while (cmd->command[++i])
				printf(" - %s\n", cmd->command[i]);
			free(input);
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
