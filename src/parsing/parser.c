/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/09 18:30:01 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_token *token_list, t_ast **ast, t_shell *sh)
{
	*ast = parse_logical(&token_list, sh);
	if (token_list)
		syntax_error();
	if (sh->parsing_error)
		return (report_syntax_error);
	return (EXIT_FAILURE);
}
t_ast	*parse_logical(t_token **token_list, t_shell *sh)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	logic_operator;

	left = parse_redirection(token_list, sh);
	while (is_operator(token_list))
	{
		logic_operator = (*token_list)->type;
		*token_list = (*token_list)->next;
		right = parse_redirection(token_list, sh);
		left = create_ast_logical(left, logic_operator, right, sh);
	}
	return (left);
}

t_ast	*parse_pipeline(t_token **token_list, t_shell *sh)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_redirection(token_list, sh);
	while (*token_list && (*token_list)->type == PIPE)
	{
		*token_list = (*token_list)->next;
		right = parse_redirection(token_list, sh);
		left = create_ast_pipeline(left, right, sh);
	}
	return (left);
}

t_ast	*parse_redirection(t_token **token_list, t_shell *sh)
{
	t_ast	*prefix;
	t_ast	*suffix;
	t_ast	*command;

	prefix = parse_redirection_list(token_list, NULL, sh);
	if (sh->parsing_error)
		return (NULL);
	command = parse_subshell(token_list, sh);
	suffix = parse_redirection_list(token_list, NULL, sh);
	if (sh->parsing_error)
		return (NULL);
	return (build_redir_cmd(prefix, suffix, command));
}

t_ast	*parse_redirection_list(t_token **token_list, t_ast *command, t_shell *sh)
{
	t_ast	*first;
	t_ast	*last;
	t_ast	*new;

	first = NULL;
	
}
/* t_command	*handle_single_command(t_token *tokens)
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
} */
