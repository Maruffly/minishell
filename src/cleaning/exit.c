/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:48:21 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:58:31 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_shell(int exit_status, t_shell *sh)
{
	if (sh)
	{
		if (sh->in_main_process && isatty(STDIN_FILENO))
			ft_write_fd("exit\n", STDERR_FILENO);
		clear_prompt(sh);
		ft_lstclear(&sh->env, free_env_var);
		ft_lstclear(&sh->allocated_pointers[SH], free);
	}
	rl_clear_history();
	exit(exit_status);
}
