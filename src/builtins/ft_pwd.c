/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:18:25 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/11 15:40:47 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../includes/minishell.h"

void	exec_pwd(t_env_list *env_list)
{
	char	*pwd;

	pwd = getenv("PWD");
	if (!pwd)
	{
		perror("PWD not set");
		return ;
	}
	printf("%s\n", pwd);
}
