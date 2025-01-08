/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:22:15 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/08 15:43:55 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*node_expansion(t_ast *node, t_shell *sh)
{
	if (node->type == AST_COMMAND)
		command_expansion(node, sh);
	else if (node->type == AST_REDIRECTION)
		redirection_expansion(node, sh);
	return (node);
}

void	command_expansion(t_ast *node, t_shell *sh)
{
	char	**args;
	t_token	*expanded_args;

	expanded_args = NULL;
	args = node->u_data.command.args;
	while (*args)
	{
		arg_expansion(*args, &expanded_args, sh);
		args++;
	}
	node->u_data.command.args = list_to_array(&expanded_args, sh);
}

void	redirection_expansion(t_ast *node, t_shell *sh)
{
	char	*str;
	t_token	*expanded_args;

	expanded_args = NULL;
	if (node->u_data.redirection.direction == HEREDOC)
		return ;
	str = node->u_data.redirection.file;
	arg_expansion(str, &expanded_args, sh);
	if (ft_lstsize_token(expanded_args) != 1 || !ft_strcmp(expanded_args->value
		, ""))
		error("wrong redirection", NULL, 1, sh);
	else
		node->u_data.redirection.file = expanded_args->value;
}

void	arg_expansion(char *str, t_token **expanded_args, t_shell *sh)
{
	t_expand	exp;
	
	if (!init_expansion(&exp, str, expanded_args, sh))
		return ;	
	while (str[exp.i])
	{
		if (exp.context == NO_QUOTE)
			no_quote(str, &exp, sh);
		else if (exp.context == IN_SINGLE_QUOTE)
			single_quote(str, &exp);
		else if (exp.context == IN_DOUBLE_QUOTE)
			double_quote(str, &exp, sh);
		if (str[exp.i])
			exp.i++;
	}
	if (exp.context == IN_SINGLE_QUOTE || exp.context == IN_DOUBLE_QUOTE)
		error("expansion", "unclosed quote", EXIT_FAILURE, sh);
	add_token_to_list(&exp, sh);
}
