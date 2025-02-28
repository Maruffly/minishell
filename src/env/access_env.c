/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:03:52 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*env_var(char *name, t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)(env->content);
		if (ft_strcmp(name, var->name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*name(t_list *env)
{
	if (!env)
		return (NULL);
	return (((t_var *)(env->content))->name);
}

char	*value(t_list *env)
{
	if (!env)
		return (NULL);
	return (((t_var *)(env->content))->value);
}
