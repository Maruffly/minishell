/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/11 16:07:14 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast	*parse_pipe(t_token **token, t_shell *sh)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_redirection(token, sh);
	while (*token && (*token)->type == PIPE)
	{
		*token = (*token)->next;
		right = parse_redirection(token, sh);
		left = create_ast_pipeline(left, right, sh);
	}
	return (left);
}

static t_ast	*parse_logical(t_token **token, t_shell *sh)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	logic_op;

	left = parse_pipe(token, sh);
	if (sh->parsing_error)
		return (NULL);
	while (is_operator(*token))
	{
		logic_op = (*token)->type;
		*token = (*token)->next;
		right = parse_pipe(token, sh);
		left = create_ast_logical(left, logic_op, right, sh);
	}
	return (left);
}

static t_ast	*parse_subshell(t_token **token, t_shell *sh)
{
	t_ast	*content;

	if (is_open_parenthesis(*token))
	{
		*token = (*token)->next;
		content = parse_logical(token, sh);
		if (*token && is_close_parenthesis(*token))
		{
			*token = (*token)->next;
			if ((*token) && is_word(*token))
				return (syntax_error((*token)->value, sh));
			return (create_ast_subshell(content, sh));
		}
		else if (*token == NULL)
			return (syntax_error("\\n", sh));
		else
			return (syntax_error((*token)->value, sh));
	}
	else if (is_close_parenthesis(*token))
		return (syntax_error(")", sh));
	return (parse_command(token));
}

t_ast	*parse_redirection(t_token **token, t_shell *sh)
{
	t_ast	*prefix;
	t_ast	*command;
	t_ast	*suffix;

	if (!token || !*token)
		return (NULL);
	prefix = parse_redirection_list(token, NULL, sh);
	if (sh->parsing_error)
		return (NULL);
	command = parse_subshell(token, sh);
	suffix = parse_redirection_list(token, command, sh);
	if (sh->parsing_error)
		return (NULL);
	return (build_redir_cmd(prefix, suffix, command));
}

int	parser(t_token *token, t_ast **ast, t_shell *sh)
{
	*ast = parse_logical(&token, sh);
	if (token)
	{
		ft_free_split((*ast)->u_data.command.args);
		free(*ast);
		*ast = NULL;
		syntax_error("...", sh);
		return (report_syntax_error(sh));
	}
	return (EXIT_SUCCESS);
}
