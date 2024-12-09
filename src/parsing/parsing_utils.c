/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/09 13:49:19 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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
	cmd->input_fd = STDIN_FILENO;
	cmd->output_fd = STDOUT_FILENO;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append_mode = false;
	cmd->heredoc_mode = false;
	cmd->heredoc_limiter = NULL;
	cmd->logical_operator = 0;
	cmd->type = CMD;
	cmd->error = false;
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

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return;
	if (!*head)
	{
		*head = new_token;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
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
	if ((new_token->type == REDIRECT_IN || new_token->type == REDIRECT_OUT
		|| new_token->type == APPEND_OUT || new_token->type == HEREDOC)
		&& (!head || !head->next))
		{
			ft_putstr_fd("Syntax error: invalid redirection missing argument\n", STDERR_FILENO);
			return (false);
}
	return (true);
}

bool	is_blank_line(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!is_blank(*line))
			return (false);
		line++;
	}
	return (true);
}

t_command	*handle_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	return (NULL);
}

/*
static void	handle_command_not_found(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}
*/


bool	is_empty_line(char *input)
{
	int	i;

	if (!input) // Si la ligne est NULL (sécurité supplémentaire)
		return (true);
	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (input[i] == '\0'); // Retourne true si la ligne est vide après trim
}

/* int	dup_value(t_token *cur, char **args, int count)
{
	int	i;

	i = 0;
	while (cur && i < count)
	{
		if (!is_separator(cur->type))
		{
			args[i] = ft_strdup(cur->value);
			if (!args[i])
			{
				while (i > 0)
				{
					free(args[i - 1]);
					i--;
				}
				args[0] = NULL;
				return (0);
			}
			i++;
		}
		cur = cur->next;
	}
	args[i] = NULL;
	return (1);
} */

char	**token_to_args(t_token *tokens, t_token *stop_token)
{
	t_token	*cur;
	int		count;
	char	**args;

	if (!tokens)
		return (NULL);
	cur = tokens;
	count = 0;
	while (cur && cur != stop_token)
	{
		if (cur->type == CMD || cur->type == ARG)
			count++;
		cur = cur->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	cur = tokens;
	count = 0;
	while (cur && cur != stop_token)
	{
		if (cur->type == CMD || cur->type == ARG)
			args[count++] = ft_strdup(cur->value);
		cur = cur->next;
	}
	args[count] = NULL;
	/* if (!dup_value(tokens, args, count))
		return (free(args), NULL); */

	return (args);
}

void add_argument_to_command(t_command *cmd, char *arg)
{
	int count;
	char **new_args;
	int	i;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return;
	i = 0;
	while (i++ < count)
		new_args[i] = cmd->args[i];
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}
