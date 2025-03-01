/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 10:10:17 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

int	print_env(bool export_format, t_list *env, t_shell *sh)
{
	while (env)
	{
		if (!export_format && !value(env))
		{
			env = env->next;
			continue ;
		}
		if (export_format)
			ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(name(env), STDOUT_FILENO);
		if (value(env))
			ft_putstr_fd("=", STDOUT_FILENO);
		if (export_format && value(env))
			ft_putstr_fd("\"", STDOUT_FILENO);
		if (value(env))
			ft_putstr_fd(value(env), STDOUT_FILENO);
		if (export_format && value(env))
			ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

char	**env_to_char_array(t_shell *sh)
{
	char	**env_array;
	char	*name_and_equal;
	int		i;
	t_list	*env;

	env = sh->env;
	env_array = safe_calloc(ft_lstsize(env) + 1, sizeof(char *), PROMPT, sh);
	i = 0;
	while (env)
	{
		if (value(env))
		{
			name_and_equal = safe_strjoin(name(env), "=", PROMPT, sh);
			env_array[i] = safe_strjoin(name_and_equal, value(env), PROMPT, sh);
			i++;
		}
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
