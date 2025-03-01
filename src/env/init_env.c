/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:15:56 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 10:09:52 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*init_env(char **env, t_shell *sh)
{
	char	*equal_sign;
	char	*name;
	t_list	*env_list;
	char	*saved_home;

	env_list = NULL;
	while (*env)
	{
		equal_sign = ft_strchr(*env, '=');
		name = safe_alloc(ft_substr(*env, 0, equal_sign - *env), PROMPT, sh);
		add_new_env_var(name, equal_sign + 1, &(env_list), sh);
		env++;
	}
	if (!env_var("PATH", env_list))
		add_new_env_var("PATH", DEFAULT_PATH, &(env_list), sh);
	saved_home = value(env_var("HOME", env_list));
	if (saved_home)
		sh->home = safe_strdup(saved_home, SH, sh);
	else
		sh->home = NULL;
	return (env_list);
}

void	add_new_env_var(char *name, char *value, t_list **list, t_shell *sh)
{
	t_var	*var;

	var = safe_calloc(1, sizeof(t_var), ONLY_CHECK, sh);
	var->name = safe_strdup(name, ONLY_CHECK, sh);
	var->value = NULL;
	if (value)
		var->value = safe_strdup(value, ONLY_CHECK, sh);
	safe_lst_addback(var, list, ONLY_CHECK, sh);
}

void	edit_env_value(t_list *in_env, char *new_value, bool add, t_shell *sh)
{
	t_var	*var;
	char	*tmp;

	var = (t_var *)(in_env->content);
	tmp = var->value;
	if (!new_value)
		var->value = NULL;
	else if (add)
		var->value = safe_strjoin(var->value, new_value, ONLY_CHECK, sh);
	else
		var->value = safe_strdup(new_value, ONLY_CHECK, sh);
	free(tmp);
}
