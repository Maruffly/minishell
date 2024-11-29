/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/29 18:32:37 by jmaruffy         ###   ########.fr       */
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
	/* int i;
	for (i = 0; commands->args[i]; i++)
		printf("ARG[%d] : %s\n", i, commands->args[i]); */
	free_token_list(tokens);
	return (commands);
}

t_token	*create_token(char *input, int *pos, t_env_list *env_list, int exit_status, bool *is_first_token)
{
	char	*value;
	t_token	*token;

	value = NULL;
	while (input[*pos] && !is_blank(input[*pos]) /* && !is_metachar(input[*pos])*/)
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
	token = init_token(value, get_token_type(value, is_first_token));
	/*printf("Token value : %s\n", token->value);
	printf("Token type : %u\n", token->type); */
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
			printf("Token : %s\n", new_token->value);
			add_token(&head, new_token);
		}
	}
	return (head);
}

bool	handle_redirections(t_token *cur, t_command *cmd)
{
	if (!cur || !cmd)
		return (false);
	if (cur->type == REDIRECT_IN)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(cur->next->value);
		cmd->input_fd = open(cmd->infile, O_RDONLY);
		if (cmd->input_fd < 0)
		{
			perror("Error opening input file");
			cmd->error = true;
			return (false);
		}
	}
	else if (cur->type == REDIRECT_OUT)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(cur->next->value);
		cmd->output_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->output_fd < 0)
		{
			perror("Error opening output file");
			cmd->error = true;
			return (false);
		}
	}
	else if (cur->type == APPEND_OUT)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(cur->next->value);
		cmd->output_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->output_fd < 0)
		{
			perror("Error opening output file");
			cmd->error = true;
			return (false);
		}
		cmd->append_mode = true;
	}
	else if (cur->type == HEREDOC) // '<<'
	{
		if (cmd->heredoc_limiter)
			free(cmd->heredoc_limiter);
		cmd->heredoc_limiter = ft_strdup(cur->next->value);
		cmd->heredoc_mode = true;
	}
	return (true);
}

void handle_pipeline(t_command **head, t_command **cmd, t_token *start, t_token *stop) {
	if (!*cmd)
		return;
	(*cmd)->args = token_to_args(start, stop);
	add_command(head, *cmd);
	*cmd = NULL;
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*head;
	t_command	*cmd;
	t_token		*cur;
	t_token		*start;
	t_token		*stop;

	head = NULL;
	cmd = NULL;
	start = tokens;
	cur = tokens;
	if (!tokens)
		return (NULL);
	while (cur)
	{
		if (cur->type == CMD)
		{
			if(!cmd)
				cmd = init_command();
			cmd->command = ft_strdup(cur->value);
			start = cur;
		}
		else if (is_redirection(cur->type))
		{
			if (!handle_redirections(cur, cmd))
				return (free_cmd_list(cmd), NULL);
			cur = cur->next;
		}
		else if (cur->type == PIPE || cur->next == NULL)
		{
			if (cur->type == PIPE)
				stop = cur;
			else
				stop = cur->next;
			handle_pipeline(&head, &cmd, start, stop);
				/* if (cmd->args)
				{
					printf("Command + arguments:\n");
					for (int i = 0; cmd->args[i] != NULL; i++)
					{
						printf("ARG[%d]: %s\n", i, cmd->args[i]);
					}
					printf("infile: %s\n", cmd->infile);
					printf("outfile: %s\n", cmd->outfile);
				} */
			start = cur->next;
		}
		cur = cur->next;
	}
	return (head);
}
