/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:09:49 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/19 16:06:54 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_invalid_identifier(char *arg, char *var_name,
										char *var_value, t_shell *sh)
{
	ft_putstr_fd("Omar&Fred: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	sh->last_status = 1;
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
}

static void	process_export_arg(t_env_list *env_list, char *arg, t_shell *sh)
{
	char	*var_name;
	char	*var_value;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	var_name = NULL;
	var_value = NULL;
	if (equal_sign)
	{
		var_name = ft_substr(arg, 0, equal_sign - arg);
		var_value = ft_strdup(equal_sign + 1);
	}
	else
		var_name = ft_strdup(arg);
	if (!is_valid_var_name(var_name))
	{
		handle_invalid_identifier(arg, var_name, var_value, sh);
		return ;
	}
	if (equal_sign)
		add_or_update_env(env_list, var_name, var_value);
	free(var_name);
	free(var_value);
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

void	exec_export(t_env_list *env_list, t_ast_command *cmd, t_shell *sh)
{
	int	i;
	int	error_occurred;

	if (!cmd->args[1])
	{
		print_export_list(env_list);
		sh->last_status = 0;
		return ;
	}
	error_occurred = 0;
	i = 1;
	while (cmd->args[i])
	{
		process_export_arg(env_list, cmd->args[i], sh);
		if (sh->last_status == 1)
			error_occurred = 1;
		i++;
	}
	if (error_occurred == 1)
		sh->last_status = 1;
	else
		sh->last_status = 0;
}
