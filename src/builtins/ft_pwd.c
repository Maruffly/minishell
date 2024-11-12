/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:18:25 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 16:35:09 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"

void	exec_pwd(t_env_list *env_list)
{
	t_env_node	*pwd;

	pwd = find_env_node(env_list, "PWD");
	if (!pwd)
	{
		perror("PWD not set");
		return ;
	}
	printf("%s\n", pwd->var_value);
}
