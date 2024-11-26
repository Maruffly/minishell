/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/26 11:28:10 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

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

bool	is_separator(t_token_type type)
{
	if (type == PIPE || type == AND || type == OR || type == PAR)
		return (true);
	return (false);
}

void	dup_value(t_token *cur, char **args, int count)
{
	int	i;

	i = 0;
	while (cur && !is_separator(cur->type) && i < count)
	{
		args[i] = ft_strdup(cur->value);
		if (!args[i])
		{
			while (i > 0)
			{
				free(args[i - 1]);
				i--;
			}
			free(args);
			return ;
		}
		i++;
		cur = cur->next;
	}
	args[i] = NULL;
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

char	**token_to_args(t_token *tokens)
{
	t_token	*cur;
	int		count;
	char	**args;

	if (!tokens)
		return (NULL);

	cur = tokens;
	count = 0;
	while (cur && !is_separator(cur->type))
	{
		count++;
		cur = cur->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	cur = tokens;
	dup_value(cur, args, count);
	return (args);
}

void	add_token(t_token **head, t_token *new_token)
{
	if (!head || !new_token)
		return;
	new_token->next = *head;
	*head = new_token;
}

bool	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' ||
			c == '(' || c == ')');
}

bool	is_syntax_ok(t_token *new_token, t_token *head)
{
	if (!head && new_token->type == PIPE)
	{
		printf("Syntax error : unexpected token '|'\n ");
		return (false);
	}
	if (new_token->type == PIPE && (!head || !head->next))
	{
		printf("Syntax error : incomplete pipe sequence\n");
		return (false);
	}
	if ((new_token->type == REDIRECT_IN || new_token->type == REDIRECT_OUT) &&
		(!new_token->next || new_token->next->type != ARG))
	{
		printf("Syntax error : invalid redirection\n");
		return (false);
	}
	return (true);
}
