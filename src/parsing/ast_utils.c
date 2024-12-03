/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:54:38 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/03 17:16:51 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"
#include "../../includes/exec.h"

t_ast	*ast_from_tokens(t_token *tokens) // call dans parse_inputs
{
	t_ast	*node;

	if (!tokens)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = tokens->type;
	node->value = ft_strdup(tokens->value);
	node->left = NULL;
	node->right = NULL;
	if (tokens->type == AND || tokens->type == OR)
	{
		node->left = ast_from_tokens(tokens->prev);
		node->right = ast_from_tokens(tokens->next);
	}
	return (node);
}

t_command	*merge_commands(t_command *left, t_command *right, t_token_type operator)
{
	t_command	*last_left;

	if (!left)
		return (right);
	if (!right)
		return (left);
	last_left = left;
	while (last_left->next)
		last_left = last_left->next;
	last_left->next = right; // merge cmd droite a la fin de la gauche
	last_left->type = operator; // attribue operateur logique
	return (left); // retour cmd mergee
}

t_command	*parse_ast_to_commands(t_ast *node) // call dans parse_inputs
{
	t_command	*commands;
	t_command	*left_commands;
	t_command	*right_commands;
	
	if (!node)
		return (NULL);
	if (node->type == CMD)
	{
		commands = init_command();
		commands->command = ft_strdup(node->value);
		return (commands);
	}
	else if (node->type == AND || node->type == OR || node->type == PIPE)
	{
		left_commands = parse_ast_to_commands(node->left);
		right_commands = parse_ast_to_commands(node->right);
		return (merge_commands(left_commands, right_commands, node->type)); // to do 
	}
	return (NULL);
}



t_command	*ast_to_command(t_ast *node)
{
	t_command	*cmd;

	if (!node || node->type != CMD)
		return (NULL);
	cmd = init_command();
	cmd->command = ft_strdup(node->value);
	cmd->args = ft_split(node->value, ' ');
	if (!cmd->args)
	{
		free(cmd->command);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

t_command	*ast_to_pipeline(t_ast *node)
{
	t_command	*pipeline;

	pipeline = NULL;
	if (node->type == PIPE)
	{
		pipeline = ast_to_command(node->left);
		pipeline->next = ast_to_pipeline(node->right);
	}
	else
		pipeline = ast_to_command(node);
	return (pipeline);
}