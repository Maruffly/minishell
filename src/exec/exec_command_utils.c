/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:45:33 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/10 17:56:15 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"



char	**convert_env_list_to_array(t_env_list *env_list)
{
	int			i;
	char		**envp;
	t_env_list	*current;
	
	i = 0;
	current = env_list;
	while (current)
	{
		i++;
		current = current->next;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	current = env_list;
	while (current)
	{
		envp[i] = ft_strjoin(current->var_name, "=");
		envp[i] = ft_strjoin(envp[i], current->var_value);
		i++;
		current = current->next;
	}
	return (envp);
}
