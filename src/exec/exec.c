/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:33:30 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/24 00:00:38 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int execute(t_ast *node, t_exit end, t_shell *sh)
{
	int status;
	bool had_redirection_error;

	(void)end;
	status = EXIT_FAILURE;
	if (!node)
		return (EXIT_FAILURE);
	
	if (node->type == AST_COMMAND || node->type == AST_REDIRECTION)
		node_expansion(node, sh);
	
	if (node->type == AST_LOGICAL)
	{
		status = exec_logical(&node->u_data.logical, sh);
	}
	else if (node->type == AST_PIPELINE)
	{
		had_redirection_error = sh->redirection_error;
		
		if (had_redirection_error)
		{
			sh->redirection_error = false;
			status = exec_pipeline(node, sh);
			sh->redirection_error = had_redirection_error;
		}
		else
			status = exec_pipeline(node, sh);
	}
	else if (node->type == AST_REDIRECTION)
		status = exec_redirection(&node->u_data.redirection, sh);
	else if (node->type == AST_SUBSHELL)
	{
		status = exec_subshell(&node->u_data.subshell, sh);
	}
	else if (node->type == AST_COMMAND)
	{
		if (!sh->redirection_error)
			status = exec_command(&node->u_data.command, end, sh);
		else
			status = EXIT_FAILURE;
	}
	if (node->type != AST_PIPELINE || !sh->redirection_error)
		sh->redirection_error = false;
	sh->redirection_error = false;
	return (status);
} */

int execute(t_ast *node, t_exit end, t_shell *sh)
{
	int status;
	bool had_redirection_error;

	(void)end;
	status = EXIT_FAILURE;
	if (!node)
		return (EXIT_FAILURE);
	
	if (node->type == AST_COMMAND || node->type == AST_REDIRECTION)
		node_expansion(node, sh);
	
	if (node->type == AST_LOGICAL)
		status = exec_logical(&node->u_data.logical, sh);
	else if (node->type == AST_PIPELINE)
	{
		/* had_redirection_error = sh->redirection_error;
    	sh->redirection_error = false;
    	status = exec_pipeline(node, sh);
    	if (had_redirection_error)
        	sh->redirection_error = true; */
	
		had_redirection_error = sh->redirection_error;
		if (had_redirection_error)
		{
			sh->redirection_error = false;
			if (node->u_data.pipeline.right->type == AST_PIPELINE)
				status = execute(node->u_data.pipeline.right, end, sh);
			else
				status = execute(node->u_data.pipeline.right, end, sh);
			sh->redirection_error = had_redirection_error;
		}
		else
			status = exec_pipeline(node, sh);
	}

	else if (node->type == AST_REDIRECTION)
		status = exec_redirection(&node->u_data.redirection, sh);
	else if (node->type == AST_SUBSHELL)
		status = exec_subshell(&node->u_data.subshell, sh);
	else if (node->type == AST_COMMAND)
	{
		if (!sh->redirection_error)
			status = exec_command(&node->u_data.command, end, sh);
		else
			status = EXIT_FAILURE;
	}
	if (node->type != AST_PIPELINE || !sh->redirection_error)
		sh->redirection_error = false;
	return (status);
}
