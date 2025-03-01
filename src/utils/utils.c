/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:48:01 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 09:58:37 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_arg_to_array(char ***array, char *new_arg, t_shell *sh)
{
	char	**new_array;
	int		i;

	new_array = safe_calloc(count_args(*array) + 2, sizeof(char *), PROMPT, sh);
	i = 0;
	while (array && (*array)[i])
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[i] = new_arg;
	new_array[i + 1] = NULL;
	*array = new_array;
}

int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}
