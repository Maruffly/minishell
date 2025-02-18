/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:14:26 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/18 12:45:01 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(char *context, char *description, int exit_status,
	t_shell *sh)
{
	ft_putstr_fd("Omar&Fred: ", STDERR_FILENO);
	ft_putstr_fd(description, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(context, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit_shell(exit_status, sh);
}

void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (!tokens->is_freed)
		{
			if (tokens->value)
			{
				free(tokens->value);
				tokens->value = NULL;
			}
			tokens->node = NULL;
			tokens->is_freed = true;
			free(tokens);
		}
		tokens = tmp;
	}
}

void	remove_list_node(t_token **node, t_token **head,
		void (*free_function)(void *), bool free_node)
{
	t_token	*to_remove;

	if (!node || !*node)
		return ;
	to_remove = *node;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	else
		*head = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	if (free_node)
		ft_lstdelone_token(to_remove, free_function);
}

void	free_ast(t_ast *ast)
{
	if (!ast || ast->is_freed)
		return ;
	ast->is_freed = true;
	if (ast->type == AST_COMMAND && ast->u_data.command.args)
		ft_free_split(ast->u_data.command.args);
	else if (ast->type == AST_REDIRECTION)
	{
		ast->u_data.redirection.file = NULL;
		free_ast(ast->u_data.redirection.command);
	}
	else if (ast->type == AST_PIPELINE)
	{
		free_ast(ast->u_data.pipeline.left);
		free_ast(ast->u_data.pipeline.right);
	}
	else if (ast->type == AST_LOGICAL)
	{
		free_ast(ast->u_data.logical.left);
		free_ast(ast->u_data.logical.right);
	}
	else if (ast->type == AST_SUBSHELL)
		free_ast(ast->u_data.subshell.child);
	free(ast);
	ast = NULL;
}

void	free_list_token(t_token *token_list)
{
	t_token	*cur;
	t_token	*next;

	cur = token_list;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}
