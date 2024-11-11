/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:10 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/08 15:14:22 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../includes/minishell.h"

void	exec_cd(t_command *cmd)
{
	char	*path;

	if (!cmd->right || !cmd->right->value)
	{
		path = getenv("HOME");
		if (!path)
			ft_putstr_fd("cd: Home not set", 2);
	}
	else
		path = cmd->right->value;
	if (chdir(path) == -1)
		perror("path does not exist");
	else
		update_pwd_env();
}

