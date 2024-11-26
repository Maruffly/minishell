/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:27:17 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/26 11:25:17 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

t_command	*parse_input(char *input, t_env_list *env_list, int exit_status)
{
	t_token		*tokens;
	t_command	*commands;
	
	tokens = tokenize_input(input, env_list, exit_status); // 1. tokenization de l'input
	if (!tokens)
	{
		ft_putstr_fd("Syntax error : invalid input\n", 2);
		return (NULL);
	}
	commands = parse_tokens(tokens); // 2. parsing des tokens en commandes
	free_token_list(tokens);
	if (!commands)
	{
		ft_putstr_fd("Parsing error : no commands generated\n", 2);
		return (NULL);
	}
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
			add_char_to_value(&value, input[*pos]);
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
