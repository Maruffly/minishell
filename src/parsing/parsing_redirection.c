/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 12:27:50 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parse_redirection(t_list **token, t_shell *sh)
{
	t_ast	*prefix;
	t_ast	*suffix;
	t_ast	*command;

	prefix = parse_redirection_list(token, NULL, sh);
	if (sh->parsing_error)
		return (NULL);
	command = parse_subshell(token, sh);
	suffix = parse_redirection_list(token, command, sh);
	if (sh->parsing_error)
		return (NULL);
	return (build_redirected_command(prefix, suffix, command));
}

static bool	parse_new_command_arg(t_list **token, t_ast *command, t_shell *sh)
{
	if (is_type(token, 1, WORD) && command)
	{
		add_arg_to_array(&command->u_data.command.args, value(*token), sh);
		*token = (*token)->next;
		return (true);
	}
	return (false);
}

static bool	is_in_sequential_redirection_list(t_list **token, t_ast *command)
{
	if (is_type(token, 4, REDIRECT_IN, REDIRECT_OUT, APPEND_OUT,
			HEREDOC))
		return (true);
	if (is_type(token, 1, WORD) && command)
		return (true);
	return (false);
}

t_ast	*parse_redirection_list(t_list **token, t_ast *command, t_shell *sh)
{
	t_ast	*first;
	t_ast	*last;
	t_ast	*new;

	first = NULL;
	while (is_in_sequential_redirection_list(token, command))
	{
		if (parse_new_command_arg(token, command, sh))
			continue ;
		new = create_ast_redirection(type(*token), (*token)->next, NULL, sh);
		if (!new)
			return (NULL);
		if (!first)
		{
			first = new;
			last = new;
		}
		else
		{
			last->u_data.redirection.child = new;
			last = new;
		}
		*token = (*token)->next->next;
	}
	return (first);
}
