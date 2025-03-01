/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:28:12 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/03/01 09:34:40 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_unset(t_ast_command *cmd, t_shell *sh)
{
	t_list	*env_var_node;

	cmd->args++;
	while (*(cmd->args))
	{
		env_var_node = env_var(*(cmd->args), sh->env);
		remove_list_node(&env_var_node, &(sh->env), free_env_var, true);
		cmd->args++;
	}
	return (EXIT_SUCCESS);
}
