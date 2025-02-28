/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:34:24 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/28 20:00:27 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env(t_ast_command *cmd, t_shell *sh)
{
	if (count_strs(cmd->args) > 1)
	{
		report_error("env: ", NULL, "too many arguments", sh);
		return (EXIT_FAILURE);
	}
	print_env(false, sh->env, sh);
	return (EXIT_SUCCESS);
}
