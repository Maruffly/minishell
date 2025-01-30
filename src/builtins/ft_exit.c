/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:21:14 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/30 17:05:18 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_exit(t_shell *sh, t_ast_command *cmd)
{
	if (!sh || !cmd->args[1])
		exit(sh->last_status);
	if (ft_isalnum(ft_atoi(cmd->args[1])))
		error("numeric argument required", cmd->args[1], 2, sh);
	sh->last_status = ft_atoi(cmd->args[1]) % 256;
	exit(sh->last_status);
}
