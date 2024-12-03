/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/03 18:12:38 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/parsing.h"
#include "../../includes/minishell.h"
#include "../../includes/exec.h"



t_command	*parse_input(char *input, t_env_list *env_list, int exit_status)
{
	t_token		*tokens;
	t_command	*commands;
	t_ast		*ast;

	if (!input || is_blank_line(input))
		return (NULL);
	tokens = tokenize_input(input, env_list, exit_status);

/*
	for (t_token *cur = tokens; cur; cur = cur->next)
		printf("Token: type=%d, value=%s\n", cur->type, cur->value);
*/
	
	if (!tokens)
		return (handle_error("Syntax error : invalid input\n"));
	ast = ast_from_tokens(tokens);
	free_token_list(tokens);
	if (!ast)
		return (handle_error("Parsing error : AST construction failed\n"));
	commands = parse_ast_to_commands(ast);
	free_ast(ast);
	return (commands);
}

/*

VERSION DE BASE


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
	// int i;
	// for (i = 0; commands->args[i]; i++)
	// 	printf("%s\n", commands->args[i]); 
	free_token_list(tokens);
	return (commands);
}
*/


t_token	*create_token(char *input, int *pos, t_env_list *env_list, int exit_status, int *is_first_token)
{
	char	*value;
	t_token	*token;

	skip_whitespace(input, pos);
	if (input[*pos] == '(' || input[*pos] == ')')
		value = handle_parentheses(input, pos);
	else
	{
		value = NULL;
		handle_all_tokens(input, pos, &value, env_list, exit_status);
	}
	if (!value)
		return (free_token_value(value));
	
	// Passe is_first_token à get_token_type
	token = init_token(value, get_token_type(value, *is_first_token));
	if (!token)
		return (free_token_value(value));

	// Une fois que le premier token (CMD) est traité, tous les autres deviennent ARG
	if (*is_first_token && token->type == CMD)
		*is_first_token = 0;

	return (token);
}



/*
/////////////////////////// ANCIENNE VERSION 3.0
t_token	*create_token(char *input, int *pos, 
						t_env_list *env_list, int exit_status)
{
	char	*value;
	t_token	*token;

	skip_whitespace(input, pos);
	if (input[*pos] == '(' || input[*pos] == ')')
		value = handle_parentheses(input, pos);
	else
	{
		value = NULL;
		handle_all_tokens(input, pos, &value, env_list, exit_status);
	}
	if (!value)
		return (free_token_value(value));
	token = init_token(value, get_token_type(value));
	if (!token)
		return (free_token_value(value));
	return (token);
}
*/


/* // ANCIENNE VERSION 2.0
t_token	*create_token(char *input, int *pos, t_env_list *env_list, int exit_status)
{
	char	*value;
	t_token	*token;

	value = NULL;
	while (input[*pos] && !is_blank(input[*pos]))
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
*/


t_token	*tokenize_input(char *input, t_env_list *env_list, int exit_status)
{
	int		pos;
	t_token	*head;
	t_token	*new_token;
	int		first_token;

	pos = 0;
	head = NULL;
	first_token = 1;
	while (input[pos])
	{
		skip_whitespace(input, &pos);
		if (input[pos])
		{
			new_token = create_token(input, &pos, env_list, exit_status, &first_token);
			if (!new_token || !is_syntax_ok(new_token, head))
			{
				free_token_list(head);
				if (new_token)
					free(new_token);
				return (NULL);
			}
/*
			printf("Created token - Type: %d, Value: %s\n", new_token->type, new_token->value);
			*/
			add_token(&head, new_token);
		}
	}
	return (head);
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*head;
	t_command	*cmd;
	t_token		*cur;

	head = NULL;
	cmd = init_command();
	if (!cmd)
		return (NULL);
	cur = tokens;
	while (cur)
	{
		if (!cmd->command)
		{
			cmd->command = ft_strdup(tokens->value);
			cmd->type = tokens->type;
		}
		/* printf("command : %s\n", cmd->command); */
		cur = cur->next;
	}
	cmd->args = token_to_args(tokens);
	add_command(&head, cmd);
	return (head);
}

bool	validate_redirections(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (!current->next || current->next->type != ARG)
			{
				ft_putstr_fd("Syntax error: redirection without argument\n", 
							STDERR_FILENO);
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}
