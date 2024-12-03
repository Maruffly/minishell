/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:14:26 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/03 16:25:46 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"
#include "../../includes/env.h"

void	free_env_node(t_env_node *node);

void	free_cmd_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			ft_free_split(cmd->args);
		if (cmd->command)
			free(cmd->command);
		free(cmd);
		cmd = tmp;
	}
}

void	free_env_list(t_env_list *list)
{
	t_env_node	*cur;
	t_env_node	*next;

	cur = list->head;
	while (cur)
	{
		next = cur->next;
		free_env_node(cur);
		cur = next;
	}
	free(list);
}

void free_token_list(t_token *tokens) 
{
	t_token *temp;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

void	free_cmd(t_command *cmd)
{
	int	i;
	
	i = 0;
	if (!cmd)
		return ;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->command)
		free(cmd->command);
	free(cmd);
}

void	free_pipe(t_command	*pipe)
{
	t_command	*current;
	t_command	*next;
	
	current = pipe;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next; 
	}
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->value)
		free(node->value);
	free(node);
}
