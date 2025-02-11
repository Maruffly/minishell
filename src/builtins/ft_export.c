/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:09:49 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/11 14:36:59 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_invalid_identifier(char *var_name, char *var_value)
{
	ft_putstr_fd("export: invalid identifier\n", 2);
	free(var_name);
	free(var_value);
}

static void	add_exported_var(t_env_list *list, char *var_name)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		handle_malloc_error();
	new_node->var_name = ft_strdup(var_name);
	handle_strdup_error(new_node->var_name);
	new_node->var_value = NULL;
	new_node->next = list->head;
	list->head = new_node;
}

void	add_or_update_env(t_env_list *list, char *var_name, char *var_value)
{
	t_env_list	*current;

	if (!list || !var_name)
		return ;
	current = list->head;
	while (current)
	{
		if (ft_strcmp(current->var_name, var_name) == 0)
		{
			free(current->var_value);
			if (var_value)
				current->var_value = ft_strdup(var_value);
			else
				current->var_value = NULL;
			return ;
		}
		current = current->next;
	}
	if (!var_value)
	{
		add_exported_var(list, var_name);
		return ;
	}
	add_env_node(list, var_name, var_value);
}

static void	process_export_arg(t_env_list *env_list, char *arg)
{
	char	*var_name;
	char	*var_value;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		var_name = ft_substr(arg, 0, equal_sign - arg);
		var_value = ft_strdup(equal_sign + 1);
	}
	else
	{
		var_name = ft_strdup(arg);
		var_value = NULL;
	}
	if (!is_valid_var_name(var_name))
		handle_invalid_identifier(var_name, var_value);
	else
	{
		add_or_update_env(env_list, var_name, var_value);
		free(var_name);
		free(var_value);
	}
}

static void	print_export_list(t_env_list *list)
{
	t_env_list	*cur;

	sort_env_list(list);
	cur = list->head;
	while (cur)
	{
		if (cur->var_name)
		{
			printf("export %s", cur->var_name);
			if (cur->var_value)
				printf("=\"%s\"", cur->var_value);
			printf("\n");
		}
		cur = cur->next;
	}
}

void	exec_export(t_env_list *env_list, t_ast_command *cmd)
{
	int	i;

	if (!cmd->args[1])
	{
		print_export_list(env_list);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		process_export_arg(env_list, cmd->args[i]);
		i++;
	}
}
