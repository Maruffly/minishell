/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/05 16:46:46 by jmaruffy         ###   ########.fr       */
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

void	read_line(void)
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
			/* printf("input : %s\n", input); */
			/* tonkenizer(input); */
			free(input);
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
	signal(SIGINT, signal_handler);
	read_line();
}
