/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:09:49 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/22 15:04:30 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"

void	exec_export(t_env_list *env_list, t_command *cmd)
{
	int		i;
	char	*var_name;
	char	*var_value;
	char	*equal_sign;

	if (!cmd->command)
	{
		print_env_list(env_list);
		return ;
	}
	i = 1;
	while (cmd->command)
	{
		equal_sign = ft_strchr(cmd->args[i], '=');
		if (equal_sign)
		{
			var_name = ft_substr(cmd->args[i], 0, equal_sign - cmd->args[i]);
			var_value = ft_strdup(equal_sign + 1);
		}
		else
		{
			var_name = ft_strdup(cmd->args[i]);
			var_value = NULL;
		}
		if (!is_valid_var_name(var_name))
		{
			ft_putstr_fd("export: invalid identifier\n", 2);
			free(var_name);
			free(var_value);
		}
		else
		{
			if (find_env_node(env_list, var_name))
				update_env_node(env_list, var_name, var_value);
			else
				add_env_node(env_list, var_name, var_value);
		}
		free(var_name);
		free(var_value);
		i++;
	}
}
