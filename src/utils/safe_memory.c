/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:32:45 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 11:20:40 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*safe_strjoin(char *s1, char *s2, t_tracking_scope scope,
	t_shell *sh)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	safe_alloc(new_str, scope, sh);
	return (new_str);
}

char	**safe_split(char *s, char c, t_tracking_scope scope, t_shell *sh)
{
	char	**new_str;
	int		i;

	new_str = ft_split(s, c);
	safe_alloc(new_str, scope, sh);
	i = 0;
	while (new_str && new_str[i])
		safe_alloc(new_str[i++], scope, sh);
	return (new_str);
}

char	*safe_strdup(char *s1, t_tracking_scope scope, t_shell *sh)
{
	char	*new_str;

	new_str = ft_strdup(s1);
	safe_alloc(new_str, scope, sh);
	return (new_str);
}
