/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:27:17 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/22 18:06:12 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

/*
Utiliser t_token pour la tokenization , et t_command pour le parsing
*/


//////////////////// MAIN FCT

t_command	*parse_input(char *input)    // OK
{
	t_token		*tokens;
	t_command	*commands;

	tokens = tokenize_input(input); // phase 1 : tokenisation de l'input
	if (!tokens)
		return (NULL);
	commands = parse_tokens(tokens); // phase 2 : parsing de l'input
	if (!commands)
		return (free_token_list(tokens), NULL);
	commands->args = token_to_args(tokens);
	/* int	i;
	for (i = 0; commands->args[i]; i++)
		printf("%s\n", commands->args[i]); */
	free_token_list(tokens); // TO DO////////////////////////////////
	return (commands); // Retourne une liste chainé de STRUCTURE
}


//////////////////// 1. TOKENIZE INPUT

char	*extract_token_value(char *input, int *pos) // version 1.0
{
	int		start;
	char	*value;

	start = *pos;
	while (input[*pos] && !is_blank(input[*pos]) && !is_operator(input, *pos))
		(*pos)++;
	value = ft_substr(input, start, *pos - start);
	return (value);
}

t_token	*init_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*create_token(char *input, int *pos)
{
	char	*value;
	t_token	*token;

	value = extract_token_value(input, pos);
	if (!value)
		return (NULL);
	token = init_token(value, identify_token_type(value));
	if (!token)
	{
		free (value);
		return (NULL);
	}
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	if (!head || !new_token)
		return;
	new_token->next = *head;
	*head = new_token;
}

t_token	*tokenize_input(char *input)     // OK
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
			new_token = create_token(input, &pos);
			if (!new_token)
			{
				free_token_list(head);
				return (NULL);
			}
			add_token(&head, new_token);
		}
	}
	return (head);
}

/*
t_token	*create_token(char *input, int *pos)     // Version 1.0
{
	t_token	*token;
	char	*value;

	value = extract_token_value(input, pos);
	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->type = identify_token_type(value);
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

*/

//////////////////// 2. PARSING INPUT

t_command	*init_command(void) // OK
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->command = NULL;
	cmd->input_fd = 0;
	cmd->output_fd = 1;
	cmd->next = NULL;
	return (cmd);
}

void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*cur;

	if (!head || !new_cmd)
		return ;
	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	cur = *head;
	while (cur->next)
			cur = cur->next;
	cur->next = new_cmd;
}

t_command	*parse_tokens(t_token *tokens) // OK
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





//////////////////// QUOTES

void	add_char_to_value(char **value, char c)
{
	size_t	len;
	char	*new_value;

	if (!value || !*value)
		return ;
	len = ft_strlen(*value);
	new_value = malloc(len + 2);  // +1 pour nouveau char , +1 pour \0
	if (!new_value)
		return ;
	ft_strcpy(new_value, *value);
	new_value[len] = c;
	new_value[len + 1] = '\0';
	free (*value);
	*value = new_value;
}

void	handle_internal_quotes(char *input, int *pos, char **value, char c) // OK
{
	if (c == '"' && input[*pos] == '/')
	{
		(*pos)++;
		if (input[*pos])
			add_char_to_value(value, input[*pos]);
	}
	else
		add_char_to_value(value, input[*pos]);
	(*pos)++;
}

void	handle_quotes(char *input, int *pos, char **value) // OK
{
	char	c;

	c = input[*pos];
	(*pos)++;
	while (input[*pos] && input[*pos] != c)
		handle_internal_quotes(input, pos, value, c);
	if (input[*pos] == c)
		(*pos)++;
}




//////////////////// EXPANSION


void	handle_expansion(char *input, int *pos, char **value)
{
	(*pos)++; // skip le '$'
	if (input[*pos] == '{')
	{
		(*pos)++;
		while (input[*pos] && input[*pos] != '}')
		{
			add_char_to_value(value, input[*pos]);
			(*pos)++;
		}
		if (input[*pos] == '}')
			(*pos)++;
	}
	else
	{
		while (input[*pos] && (ft_isalnum(input[*pos]) || input[*pos] == '_'))
		{
			add_char_to_value(value, input[*pos]);
			(*pos)++;
		}
	}
}
