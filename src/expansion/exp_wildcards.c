/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wildcards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:12 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:17:31 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*pattern_filter(t_list *files, t_exp *exp)
{
	t_list	*tmp;
	char	*full_filename;
	t_list	*next;

	tmp = files;
	while (tmp)
	{
		full_filename = (char *)tmp->content;
		if (!pattern_match(full_filename, exp->buf, 0, exp)
			|| not_explicit_hidden_file(full_filename, exp))
		{
			next = tmp->next;
			remove_list_node(&tmp, &files, NULL, false);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
	return (files);
}

bool	pattern_match(const char *filename, const char *pattern,
		int pattern_index, t_exp *exp)
{
	while (*filename && *pattern)
	{
		if (*pattern == '*' && is_active_wildcard(pattern_index, exp))
		{
			pattern++;
			pattern_index++;
			if (!*pattern)
				return (true);
			while (*filename)
			{
				if (pattern_match(filename, pattern, pattern_index, exp))
					return (true);
				filename++;
			}
			return (false);
		}
		else if (*pattern != *filename)
			return (false);
		pattern++;
		filename++;
		pattern_index++;
	}
	if (only_active_wildcard_left(pattern, exp))
		return (true);
	return (*pattern == *filename);
}

bool	not_explicit_hidden_file(const char *full_filename, t_exp *exp)
{
	const char	*filename;
	const char	*last_part_pattern;

	filename = ft_strrchr(full_filename, '/');
	if (!filename)
		filename = full_filename;
	else
		filename++;
	last_part_pattern = ft_strrchr(exp->buf, '/');
	if (!last_part_pattern)
		last_part_pattern = exp->buf;
	else
		last_part_pattern++;
	if (filename[0] == '.' && last_part_pattern[0] != '.')
		return (true);
	return (false);
}
