/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/15 19:01:46 by jbmy             ###   ########.fr       */
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

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_fd = 0;
	cmd->output_fd = 1;
	cmd->next = NULL;
	return (cmd);
}

char	**ft_add_to_array(char **array, char *new_element)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	while (array && array[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	j = 0;
	while (j < i)
		new_array[i] = array[i];
	new_array[i] = ft_strdup(new_element);
	if (!new_array[i])
		return (free(new_array), NULL);
	new_array[i + 1] = NULL;
	free(array);
	return (new_array);
}

void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*cur;

	if (!head || !new_cmd)
		return ;
	if (!*head)
		*head = new_cmd;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_cmd;
	}
}

t_command	*parse_input(char *input)
{
	char		**tokens;
	int			i;
	t_command	*head;
	t_command	*cmd;

	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		cmd = init_command();
		if (!cmd)
			return (NULL);
		cmd->type = identify_token_type(tokens[i]);
		if (cmd->type == CMD || cmd->type == ARG)
		{
			while (tokens[i] && identify_token_type(tokens[i]) == ARG)
			{
				cmd->args = ft_add_to_array(cmd->args, tokens[i]);
				i++;
			}
		}
		else if (cmd->type == PIPE || cmd->type == REDIRECT_OUT)
		{
			if (cmd->type == REDIRECT_IN || cmd->type == REDIRECT_OUT)
			{
				i++;
				if (tokens[i])
					cmd->args = ft_add_to_array(cmd->args, tokens[i]);
			}
			i++;
		}
		else
			i++;
		add_command(&head, cmd);
	}
	ft_free_split(tokens);
	return (head);
}

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
			cmd = parse_input(input);
			if (!cmd)
			{
				perror("Fail to parse input");
				free(input);
				continue ;
			}
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
