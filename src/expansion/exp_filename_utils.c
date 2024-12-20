/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:40:18 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/19 18:10:21 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_root_path(t_expand *exp, t_shell *sh)
{
	int		i;
	char	*path;

	i = exp->buf_i - 1;
	while (i >= 0 && exp->buf[i] != '/')
		i--;
	if (i == -1)
		return (ft_strdup("."));
	path = ft_calloc(i + 2, sizeof(char));
	ft_strlcpy(path, exp->buf, i + 2);
	return (path);
}

t_token	*pattern_filter(t_token *tokens, t_expand *exp)
{
	t_token	*current;
	t_token	*next;
	char	*full_filename;
	
	current = tokens;
	while (current)
	{
		full_filename = (char *)current->value;
		if (!pattern_match(full_filename, exp->buf, 0, exp)) ///// TO DO
		{
			next = current->next;
			remove_list_node(&current, &tokens, NULL, false); //// TODO 
			current = next;
		}
		else
			current = current->next;
	}
	return (tokens);
}
