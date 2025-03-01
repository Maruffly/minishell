/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:09:49 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 11:43:01 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_one(char *assignment, bool *name_error, t_shell *sh)
{
	char	*equal_sign;
	bool	add;
	char	*name;
	t_list	*in_env;

	equal_sign = ft_strchr(assignment, '=');
	add = false;
	if (ft_strnstr(assignment, "+=", equal_sign - assignment + 1))
		add = true;
	name = safe_alloc(ft_substr(assignment, 0, equal_sign - add - assignment),
			PROMPT, sh);
	if (!is_valid_name(name))
		return (report_name_error(assignment, name_error, sh));
	in_env = env_var(name, sh->env);
	if (in_env && equal_sign)
		edit_env_value(in_env, equal_sign + 1, add, sh);
	else if (!in_env && !equal_sign)
		add_new_env_var(name, NULL, &(sh->env), sh);
	else if (!in_env && equal_sign)
		add_new_env_var(name, equal_sign + 1, &(sh->env), sh);
}

void	report_name_error(char *assignment, bool *name_error, t_shell *sh)
{
	report_error("export: `", assignment, "': not a valid identifier", sh);
	*name_error = true;
}

bool	is_valid_name(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

int	exec_export(t_ast_command *cmd, t_shell *sh)
{
	bool	name_error;

	cmd->args++;
	if (!*(cmd->args))
		return (print_env(true, sh->env, sh));
	name_error = false;
	while (*(cmd->args))
	{
		export_one(*(cmd->args), &name_error, sh);
		cmd->args++;
	}
	if (name_error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
