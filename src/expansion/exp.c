/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:22:15 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/24 09:58:18 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exp_wildcard_or_arg(char *arg, t_token **expanded_args,
								t_shell *sh)
{
	char	**exp_dirs;

	if (ft_strcmp(arg, "*/") == 0)
	{
		exp_dirs = expand_wildcard_dirs();
		if (exp_dirs)
			*expanded_args = append_tokens_to_list(*expanded_args, exp_dirs);
		ft_free_split(exp_dirs);
	}
	else
		arg_expansion(arg, expanded_args, sh);
	free(arg);
}

void	filter_empty_arg(t_token **expanded_args)
{
	t_token	*cur;
	t_token	*next;
	t_token	*prev;

	cur = *expanded_args;
	while (cur)
	{
		next = cur->next;
		if (cur->value && cur->value[0] == '\0')
		{
			if (cur == *expanded_args)
				*expanded_args = next;
			else
			{
				prev = *expanded_args;
				while (prev->next != cur)
					prev = prev->next;
				prev->next = next;
			}
			free(cur->value);
			free(cur);
		}
		cur = next;
	}
}

void	command_expansion(t_ast *node, t_shell *sh)
{
	char	**args;
	int		i;
	t_token	*expanded_args;

	if (!node || !sh || !node->u_data.command.args)
		return ;
	expanded_args = NULL;
	args = node->u_data.command.args;
	i = 0;
	while (args[i])
	{
		exp_wildcard_or_arg(args[i], &expanded_args, sh);
		i++;
	}
	free(args);
	filter_empty_arg(&expanded_args);
	node->u_data.command.args = list_to_array(&expanded_args, sh);
	if (expanded_args)
		free_token_list(expanded_args);
}

void	redirection_expansion(t_ast *node, t_shell *sh)
{
	char	*filename;

	if (!node || !sh || node->u_data.redirection.direction == HEREDOC)
		return ;
	filename = remove_quotes(node->u_data.redirection.file);
	if (filename)
	{
		if (node->u_data.redirection.file_free)
			free(node->u_data.redirection.file);
		node->u_data.redirection.file = filename;
		node->u_data.redirection.file_free = true;
	}
}

t_ast	*node_expansion(t_ast *node, t_shell *sh)
{
	if (!node || !sh)
		return (NULL);
	if (node->type == AST_COMMAND)
		command_expansion(node, sh);
	else if (node->type == AST_REDIRECTION)
		redirection_expansion(node, sh);
	return (node);
}
