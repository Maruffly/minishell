/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:21:14 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/14 18:03:03 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	not_numeric_args(char **args, t_shell *sh)
{
	char	*arg;
	int		i;

	if (!args[1])
		return (false);
	i = 0;
	arg = args[1];
	while (arg[i])
	{
		if (!ft_isdigit((unsigned char)arg[i]))
		{
			error("numeric argument required", arg, 2, sh);
			sh->last_status = 2;
			sh->must_exit = true;
			return (true);
		}
		i++;
	}
	return (false);
}

void	exec_exit(t_shell *sh, t_ast_command *cmd)
{
	bool	not_num_arg;

	if (!cmd->args[1])
	{
		write(1, "exit\n", 5);
		sh->must_exit = true;
		return ;
	}
	not_num_arg = not_numeric_args(cmd->args, sh);
	if (not_num_arg)
		return ;
	not_numeric_args(cmd->args, sh);
	if (sh->env)
		ft_lstclear_env(&sh->env, free_env_list);
	rl_clear_history();
	write(1, "exit\n", 5);
	sh->last_status = ft_atoi(cmd->args[1]) % 256;
	sh->must_exit = true;
}
