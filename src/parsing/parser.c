/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/09 14:28:31 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ici on utilise un double pointeur token pour faire passer en parametre
// des fonctions la position courante dans le tableau de token.

void print_token_list_debug(t_token *token_list)
{
    t_token *current = token_list;
    while (current)
    {
        printf("Token: %s, Type: %u, Next: %p, Prev: %p\n",
               current->value, current->type,
               (void *)current->next, (void *)current->prev);
        current = current->next;
    }
}

void debug_token_print(t_token *token)
{
	printf("Current Token: value='%s', type=%d, next=%p\n",
	token->value, token->type, (void*)token->next);
}

int	parser(t_token *token, t_ast **ast, t_shell *sh)
{
	*ast = parse_logical(&token, sh);
	if (token)
		syntax_error("...", sh);
	if (sh->parsing_error)
		return (report_syntax_error(sh));
	return (EXIT_SUCCESS);
}

t_ast	*parse_logical(t_token **token, t_shell *sh)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	logic_op;

	left = parse_pipe(token, sh);
	/* if (!token || !*token)
		return (NULL); */
	/* printf("Parsing token : value='%s', type=%d, next_value=%p\n",
			(*token)->value, (*token)->type, (*token)->next->value); */
	while (is_operator(*token))
	{
		logic_op = (*token)->type;
		*token = (*token)->next;
		right = parse_pipe(token, sh);
		left = create_ast_logical(left, logic_op, right, sh);
	}
	return (left);
}

t_ast	*parse_pipe(t_token **token, t_shell *sh)
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
// Il y a forcement une commande avant la redirection ou rien : cmd > file ; > file
// Il peut y avoir des suites de redirections : cmd > file1 > file2
t_ast	*parse_redirection_list(t_token **token, t_ast *command, t_shell *sh)
{
	t_ast	*first;
	t_ast	*last;
	t_ast	*new;
	t_token	*cur;

	first = NULL; // pointeur vers premiers noeud de redir
	last = NULL;  // ... vers le dernier de la liste des redirs
	if (!token || !*token)
		return (NULL);
	cur = *token;
	while (cur)
	{
		/* printf("Parsing token REDIRECTION: value='%s', type=%d, next=%p\n",
			cur->value, cur->type, (void*)cur->next); */
		 if (is_word(cur) && command && command->type == AST_COMMAND)
		{
			if (!command->u_data.command.args ||
			!command->u_data.command.args[0])
				add_arg_tab(&command->u_data.command.args, cur->value);
			cur = cur->next;
			continue;
		}
		if (!is_redirect(cur))
			break ;
		new = create_ast_redirection(cur->type, cur->next, NULL, sh);
		if (!new)
			return (NULL);
		if (!first)
		{
			first = new;
			last = new;
		}
		else
		{
			last->u_data.redirection.command = new;
			last = new;
		}
		cur = cur->next->next;
	}
	*token = cur;
	return (first);
}

int		argu_count(t_token *cur)
{
	int	i;

	i = 0;
	while (cur && is_word(cur))
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

t_ast	*parse_command(t_token **token)
{
	t_token	*cur;
	int		arg_count;
	char	**args;
	int		i;

	/* debug_token_print(*token); */
	cur = *token;
	arg_count = argu_count(cur);
	if (!arg_count)
		return (NULL);
	args = ft_calloc((arg_count + 1), sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	cur = *token;
	while (cur && is_word(cur))
	{
		args[i] = ft_strdup(cur->value);
		if (!args)
			return (ft_free_split(args), NULL);
		/* printf("ARG_CMD : %s\n", args[i]); */
		i++;
		cur = cur->next;
	}
	args[arg_count] = NULL;
	return (create_ast_cmd(args));
}

t_ast	*parse_subshell(t_token **token, t_shell *sh)
{
	t_ast	*content;

	/* debug_token_print(*token); */
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
