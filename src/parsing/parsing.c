/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/09 14:48:24 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* t_command	*parse_input(char *input, t_env_list *env_list, int exit_status)
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
	if (!commands)
	{
		free_token_list(tokens);
		ft_putstr_fd("Parsing error : no commands generated\n", 2);
		return (NULL);
	}
	int i;
	for (i = 0; commands->args[i]; i++)
		printf("ARG[%d] : %s\n", i, commands->args[i]);
	free_token_list(tokens);
	return (commands);
}

t_token	*create_token(char *input, int *pos, t_env_list *env_list, int exit_status, bool *is_first_token)
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
		else if (is_metachar(input[*pos]))
		{
			if (input[*pos] == '>' || input[*pos] == '<')
			{
				add_char_to_value(&value, input[*pos]);
				(*pos)++;
			}
			if (input[*pos] == '>' && value[0] == '>')
			{
				add_char_to_value(&value, input[*pos]);
				(*pos)++;
			}
		}
		else
		{
			add_char_to_value(&value, input[*pos]);
			(*pos)++;
		}
	}
	if (!value)
		return (NULL);
	token = init_token(value, get_token_type(value, is_first_token));
	printf("Token value : %s\n", token->value);
	printf("Token type : %u\n", token->type);
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
	bool	is_first_token;

	is_first_token = true;
	pos = 0;
	head = NULL;
	while (input[pos])
	{
		skip_whitespace(input, &pos);
		if (input[pos])
		{
			new_token = create_token(input, &pos, env_list, exit_status, &is_first_token);
			if (!new_token || !is_syntax_ok(new_token, head))
			{
				free_token_list(head);
				if (new_token)
					free(new_token);
				return (NULL);
			}
			printf("IN tokenization - Token Type: %d\n", new_token->type);
			printf("In tokenization- Token Value: %s\n", new_token->value);
			add_token(&head, new_token);
		}
	}
	return (head);
} */

t_command	*handle_single_command(t_token *tokens)
{
	t_command	*cmd;

	cmd = init_command();
	if (!cmd)
		return (NULL);

	cmd->command = ft_strdup(tokens->value);
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args[0] = ft_strdup(tokens->value);
	cmd->args[1] = NULL;

	return (cmd);
}

t_command	*parse_tokens(t_token *tokens)
{
	t_ast		*ast;
	t_command	*commands;

	if (!tokens)
		return (NULL);
	if (!tokens->next)
		return (handle_single_command(tokens));
	ast = ast_from_tokens(tokens);
	if (!ast)
		return (NULL);
	commands = parse_ast_to_commands(ast);

	free_ast(ast);
	return (commands);
}
