/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/09 13:49:08 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	g_last_exit_status = 0;

void	set_last_exit_status(int status)
{
	g_last_exit_status = status;
}

int	get_last_exit_status(void)
{
	return (g_last_exit_status);
}


void	exec_simple_cmd(t_ast *node, t_env_list *env, int *exit_code)
{
	t_command	*cmd;

	cmd = ast_to_command(node);
	if (!cmd)
	{
		*exit_code = 1;
		return ;
	}
	execute_command(cmd, env, STDIN_FILENO);
	*exit_code = cmd->exit_code;
	free_cmd(cmd);
}

void	exec_pipe_cmd(t_ast *node, t_env_list *env, int *exit_code)
{
	t_command	*pipe;

	pipe = ast_to_pipeline(node);
	if (!pipe)
	{
		*exit_code = 1;
		return ;
	}
	execute_pipeline(pipe, env);
	*exit_code = pipe->exit_code;
	free_pipe(pipe);
}

void	exec_and_operator(t_ast *node, t_env_list *env, int *exit_code)
{
	execute_ast(node->left, env, exit_code);
	if (*exit_code == 0)
		execute_ast(node->right, env, exit_code);
}

void	exec_or_operator(t_ast *node, t_env_list *env, int *exit_code)
{
	execute_ast(node->right, env, exit_code);
	if (*exit_code != 0)
		execute_ast(node->right, env, exit_code);
}

void	execute_ast(t_ast *node, t_env_list *env, int *exit_code)
{
	if (!node)
	{
		*exit_code = 1;
		return ;
	}
	if (node->type == CMD)
		exec_simple_cmd(node, env, exit_code);
	else if (node->type == PIPE)
		exec_pipe_cmd(node, env, exit_code);
	else if (node->type == AND)
		exec_and_operator(node, env, exit_code);
	else if (node->type == OR)
		exec_or_operator(node, env, exit_code);
}


/*
void	execute_ast(t_ast *node, t_env_list *env)
{
	if (!node)
		return ;
	if (node->type == CMD)
		execute_command(ast_to_command(node), env, STDIN_FILENO);
	else if (node->type == PIPE)
		execute_pipeline(ast_to_pipeline(node), env);
	else if (node->type == AND)
	{
		execute_ast(node->left, env);
		if (get_last_exit_status() == 0) // execute a droite si gauche reussit
			execute_ast(node->right, env);
	}
	else if (node->type == OR)
	{
		execute_ast(node->left, env);
		if (get_last_exit_status() != 0) // execute a droite si gauche echoue
			execute_ast(node->right, env);
	}
}
*/
