/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:21:14 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/11 14:35:40 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_exit(t_shell *sh, t_ast_command *cmd, t_ast *ast)
{	
	(void)ast;
	write(1, "exit\n", 5);
	if (sh->env)
		ft_lstclear_env(&sh->env, free_env_list);
	rl_clear_history();
	if (!sh || !cmd->args[1])
	{
		sh->must_exit = true;
		return ;
	}
	if (ft_isalnum(ft_atoi(cmd->args[1])))
		error("numeric argument required", cmd->args[1], 2, sh);
	sh->last_status = ft_atoi(cmd->args[1]) % 256;
	sh->must_exit = true;
}
