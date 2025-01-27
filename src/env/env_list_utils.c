/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:44:40 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/27 09:45:16 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

static char	*create_envp_entry(t_env_list *current)
{
	char	*temp;
	char	*entry;

	temp = ft_strjoin(current->var_name, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, current->var_value);
	free(temp);
	if (!entry)
		return (NULL);
	return (entry);
}

char	**list_to_envp(t_env_list *env)
{
	t_env_list	*current;
	char		**envp;
	int			size;
	int			i;

	current = env->head;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	current = env->head;
	i = 0;
	while (current)
	{
		envp[i] = create_envp_entry(current);
		if (!envp[i])
		{
			ft_free_split(envp);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
