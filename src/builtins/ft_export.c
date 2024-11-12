/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:09:49 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 16:09:59 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"

void	exec_export(t_env_list *env_list, t_command *cmd)
{
	char	**args;
	int		i;
	char	*var_name;
	char	*var_value;

	if (!cmd->right)
	{
		print_env_list(env_list);
		return ;
	}
	args = ft_split(cmd->right->value, ' ');
	i = 0;
	while (args[i])
	{

		if (ft_strchr(args[i], '='))
		{
			var_name = ft_strndup(args[i], ft_strchr(args[i], '=') - args[i]);
			var_value = ft_strdup(ft_strchr(args[i], '=') + 1);
			update_env_node(env_list, var_name, var_value);
			free(var_name);
			free(var_value);
		}
		else
			printf("export: '%s' is not a valid identifier\n", args[i]);
		i++;
	}
	ft_free_split(args);
}
