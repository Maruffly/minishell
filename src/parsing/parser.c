/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/10 17:42:18 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_token *token_list, t_ast **ast, t_shell *sh)
{
	*ast = parse_logical(&token_list, sh);
	if (token_list)
		syntax_error();
	if (sh->parsing_error)
		return (report_syntax_error());
	return (EXIT_FAILURE);
}
t_ast	*parse_logical(t_token **token_list, t_shell *sh)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	logic_op;

	left = parse_redirection(token_list, sh);
	while (is_operator(token_list))
	{
		logic_op = (*token_list)->type;
		*token_list = (*token_list)->next;
		right = parse_pipe(token_list, sh);
		left = create_ast_logical(left, logic_op, right, sh);
	}
	return (left);
}

t_ast	*parse_pipe(t_token **token_list, t_shell *sh)
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
	while (is_redirect(token_list) || (is_word(token_list) && command))
	{
		if (is_word(token_list) && command)
		{
			add_arg_tab(&command->u_data.command.arg, *token_list->value)
		}
	}
}
