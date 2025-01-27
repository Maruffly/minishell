/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:09:49 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/27 15:59:28 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static void	handle_invalid_identifier(char *var_name, char *var_value)
{
	ft_putstr_fd("export: invalid identifier\n", 2);
	free(var_name);
	free(var_value);
}

static void	add_or_update_env(t_env_list *env_list, char *var_name, char *var_value)
{
	if (find_env_node(env_list, var_name))
		update_env_node(env_list, var_name, var_value);
	else
		add_env_node(env_list, var_name, var_value);
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

void exec_export(t_env_list *env_list, t_ast_command *cmd)
{
	int	i;

	if (!cmd->args[1])
	{
		print_env_list(env_list);
		return;
	}
	i = 1;
	while (cmd->args[i])
	{
		process_export_arg(env_list, cmd->args[i]);
		i++;
	}
}
