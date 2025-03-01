/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:28:12 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 12:12:10 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_from_env(t_list **env_list, char *var_name)
{
	t_list *current;
	t_list *previous;
	
	if (!env_list || !*env_list || !var_name)
		return;
		
	current = *env_list;
	previous = NULL;
	
	while (current)
	{
		t_var *var = (t_var *)(current->content);
		if (var && ft_strcmp(var->name, var_name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env_list = current->next;
				
			free_env_var(current->content);
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

int	exec_unset(t_ast_command *cmd, t_shell *sh)
{
	t_list *env_var_node;
	char *var_name;

	cmd->args++;
	while (*(cmd->args))
	{
		var_name = *(cmd->args);
		env_var_node = env_var(var_name, sh->env);
		remove_from_env(&(sh->env), var_name);
		cmd->args++;
	}
	return (EXIT_SUCCESS);
}
