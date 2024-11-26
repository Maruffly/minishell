/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/26 15:57:52 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

t_command	*parse_input(char *input, t_env_list *env_list, int exit_status)
{
	t_token		*tokens;
	t_command	*commands;

	if (!input || is_blank_line(input))
		return (NULL);
	tokens = tokenize_input(input, env_list, exit_status); // 1. tokenization de l'input
	if (!tokens)
		return (handle_error("Syntax error : invalid input\n"));
	commands = parse_tokens(tokens); // 2. parsing des tokens en commandes
	if (!commands)
	{
		free_token_list(tokens);
		return (handle_error("Parsing error : no commands generated\n"));
	}
	commands->args = token_to_args(tokens);
	// int i;
	// for (i = 0; commands->args[i]; i++)
	// 	printf("%s\n", commands->args[i]); 
	free_token_list(tokens);
	return (commands);
}

t_token	*create_token(char *input, int *pos, t_env_list *env_list, int exit_status)
{
	char	*value;
	t_token	*token;

	value = NULL;
	while (input[*pos] && !is_blank(input[*pos]) && !is_metachar(input[*pos]))
	{
		if (input[*pos] == '\'' || input[*pos] == '"')
			handle_quotes(input, pos, &value);
		else if (input[*pos] == '$')
			handle_expansion(input, pos, &value, env_list, exit_status);
		else
		{
			add_char_to_value(&value, input[*pos]);
			(*pos)++;
		}
	}
	if (!value)
		return (NULL);
	token = init_token(value, get_token_type(value));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	return (token);
}

t_token	*tokenize_input(char *input, t_env_list *env_list, int exit_status)
{
	int		pos;
	t_token	*head;
	t_token	*new_token;

	pos = 0;
	head = NULL;
	while (input[pos])
	{
		skip_whitespace(input, &pos);
		if (input[pos])
		{
			new_token = create_token(input, &pos, env_list, exit_status);
			if (!new_token || !is_syntax_ok(new_token, head))
			{
				free_token_list(head);
				if (new_token)
					free(new_token);
				return (NULL);
			}
			add_token(&head, new_token);
		}
	}
	return (head);
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*head;
	t_command	*cmd;

	head = NULL;
	while (tokens)
	{
		cmd = init_command();
		if (!cmd)
		{
			free_cmd_list(head);
			return (NULL);
		}
		cmd->command = ft_strdup(tokens->value);
		cmd->type = tokens->type;
		if (!cmd->command)
		{
			free(cmd);
			return (free_cmd_list(head), NULL);
		}
		add_command(&head, cmd);
		tokens = tokens->next;
	}
	return (head);
}
