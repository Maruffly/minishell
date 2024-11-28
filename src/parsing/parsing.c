/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/28 19:48:24 by jmaruffy         ###   ########.fr       */
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
	if (!commands)
	{
		free_token_list(tokens);
		ft_putstr_fd("Parsing error : no commands generated\n", 2);
		return (NULL);
	}
	int i;
	for (i = 0; commands->args[i]; i++)
		printf("%s\n", commands->args[i]);
	printf("\n\n");
	free_token_list(tokens);
	return (commands);
}

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
			/* printf("new token : %s\n", new_token->value); */
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

void	parse_redirections(t_token *cur, t_command *cmd)
{
	if (!cur || !cmd)
		return ;
	if (!cur->next)
	{
		ft_putstr_fd("Error: Missing file for redirection\n", STDERR_FILENO);
		cmd->error = true;
		return ;
	}
	if (cur->type == REDIRECT_IN)
		cmd->infile = ft_strdup(cur->next->value);
	else if (cur->type == REDIRECT_OUT)
	{
		cmd->outfile = ft_strdup(cur->next->value);
		cmd->append_mode = false;
	}
	else if (cur->type == APPEND_OUT)
	{
		cmd->outfile = ft_strdup(cur->next->value);
		cmd->append_mode = true;
	}
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*head;
	t_command	*cmd;
	t_token		*cur;
	t_token		*start;

	head = NULL;
	cmd = NULL;
	start = tokens;
	cur = tokens;
	if (!tokens)
		return (NULL);
	while (cur)
	{
		if (!cmd && cur->type == CMD)
		{
			cmd = init_command();
			cmd->command = ft_strdup(cur->value);
			cmd->type = cur->type;
			start = cur;
		}
		if (is_redirection(cur->type))
			parse_redirections(cur, cmd);
		if (cur->type == PIPE || cur->next == NULL)
		{
			if (cmd)
			{
				cmd->args = token_to_args(start, cur);
				add_command(&head, cmd);
				cmd = NULL;
				start = cur->next;
			}
		}
		cur = cur->next;
	}
	return (head);
}
