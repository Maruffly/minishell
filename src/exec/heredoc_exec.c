/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:14:53 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/31 17:59:03 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_signal_exit(t_heredoc *hdoc)
{
	if (g_signal_value == SIGINT)
	{
		close(hdoc->pipe_fd[1]);
		exit(130);
	}
	close(hdoc->pipe_fd[1]);
	exit(heredoc_eof_handler(hdoc));
}

static char	*handle_expansion(char *line, t_heredoc *hdoc,
			t_shell *sh, t_expand *exp)
{
	char	*expand_line;

	if (!hdoc->expand_vars)
		return (line);
	expand_line = expand_heredoc_vars(line, sh, exp);
	free(line);
	if (!expand_line)
	{
		printf("Exp failure");
		return (NULL);
	}
	return (expand_line);
}

bool	process_heredoc_line(char *line, t_heredoc *hdoc,
		t_expand *exp, t_shell *sh)
{
	char	*expanded_line;

	expanded_line = handle_expansion(line, hdoc, sh, exp);
	if (!expanded_line)
		return (false);
	if (!write_to_pipe(hdoc->pipe_fd[1], expanded_line))
		return (false);
	free(expanded_line);
	return (true);
}

static int	process_ast_redirection(t_ast *ast, t_shell *sh)
{
	int			status;
	t_expand	exp;

	ft_memset(&exp, 0, sizeof(t_expand));
	status = handle_heredoc(&ast->u_data.redirection, sh, &exp);
	if (status != EXIT_SUCCESS)
		return (status);
	return (handle_heredoc_ast(ast->u_data.redirection.command, sh));
}

int	handle_heredoc_ast(t_ast *ast, t_shell *sh)
{
	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_REDIRECTION
		&& ast->u_data.redirection.direction == HEREDOC)
		return (process_ast_redirection(ast, sh));
	if (ast->type == AST_PIPELINE)
	{
		if (handle_heredoc_ast(ast->u_data.pipeline.left, sh) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		return (handle_heredoc_ast(ast->u_data.pipeline.right, sh));
	}
	if (ast->type == AST_LOGICAL)
	{
		if (handle_heredoc_ast(ast->u_data.logical.left, sh) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		return (handle_heredoc_ast(ast->u_data.logical.right, sh));
	}
	if (ast->type == AST_SUBSHELL)
		return (handle_heredoc_ast(ast->u_data.subshell.child, sh));
	return (EXIT_SUCCESS);
}
