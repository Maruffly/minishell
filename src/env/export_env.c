/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 20:29:34 by jlaine           ###   ########.fr       */
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
			write_s("export ", STDOUT_FILENO, sh);
		write_s(name(env), STDOUT_FILENO, sh);
		if (value(env))
			write_s("=", STDOUT_FILENO, sh);
		if (export_format && value(env))
			write_s("\"", STDOUT_FILENO, sh);
		if (value(env))
			write_s(value(env), STDOUT_FILENO, sh);
		if (export_format && value(env))
			write_s("\"", STDOUT_FILENO, sh);
		write_s("\n", STDOUT_FILENO, sh);
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
	env_array = calloc_s(ft_lstsize(env) + 1, sizeof(char *), PROMPT, sh);
	i = 0;
	while (env)
	{
		if (value(env))
		{
			name_and_equal = strjoin_s(name(env), "=", PROMPT, sh);
			env_array[i] = strjoin_s(name_and_equal, value(env), PROMPT, sh);
			i++;
		}
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
