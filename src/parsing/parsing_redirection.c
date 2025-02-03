/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:36:18 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/03 15:23:00 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_arg_tab(char ***array, char *new_arg)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	while ((*array) && (*array)[i])
		i++;
	new_array = ft_calloc(i + 2, sizeof(char *));
	if (!new_array)
		return ;
	j = 0;
	while (j < i)
	{
		new_array[j] = (*array)[j];
		j++;
	}
	new_array[i] = new_arg;
	new_array[i + 1] = NULL;
	*array = new_array;
}

static bool	handle_command_argument(t_token **cur, t_ast *command)
{
	if (is_word(*cur) && command && command->type == AST_COMMAND)
	{
		if (!command->u_data.command.args || !command->u_data.command.args[0])
			add_arg_tab(&command->u_data.command.args, (*cur)->value);
		*cur = (*cur)->next;
		return (true);
	}
	return (false);
}

static t_ast	*validate_and_create_redirection(t_token **cur,
					t_ast **first, t_ast **last, t_shell *sh)
{
	t_ast	*new_redir;

	if (!(*cur)->next || !is_word((*cur)->next))
	{
		syntax_error((*cur)->value, sh);
		return (NULL);
	}
	new_redir = create_ast_redirection((*cur)->type, (*cur)->next, NULL, sh);
	if (!new_redir)
		return (NULL);
	if (!*first)
	{
		*first = new_redir;
		*last = new_redir;
	}
	else
	{
		(*last)->u_data.redirection.command = new_redir;
		*last = new_redir;
	}
	*cur = (*cur)->next->next;
	return (new_redir);
}

t_ast	*parse_redirection_list(t_token **token, t_ast *command, t_shell *sh)
{
	t_ast	*first;
	t_ast	*last;
	t_token	*cur;

	first = NULL;
	last = NULL;
	cur = *token;
	while (cur)
	{
		if (handle_command_argument(&cur, command))
			continue ;
		if (!is_redirect(cur))
			break ;
		if (!validate_and_create_redirection(&cur, &first, &last, sh))
			return (NULL);
		if (!cur)
			break ;
	}
	*token = cur;
	return (first);
}
