/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wildcards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:12 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 14:04:49 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	not_explicit_hidden_file(const char *full_filename, t_exp *exp)
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
	return (filename[0] == '.' && last_part_pattern[0] != '.');
}

static bool	pattern_match(const char *filename, const char *pattern,
	int pattern_index, t_exp *exp)
{
	if (!*pattern)
		return (!*filename);
	if (*pattern == '*' && is_active_wildcard(pattern_index, exp))
	{
		while (*filename)
		{
			if (pattern_match(filename, pattern + 1, pattern_index + 1, exp))
				return (true);
			filename++;
		}
		return (pattern_match(filename, pattern + 1, pattern_index + 1, exp));
	}
	if (*pattern == *filename)
		return (pattern_match(filename + 1, pattern + 1,
				pattern_index + 1, exp));
	return (false);
}

t_list	*add_filtered_node(t_list *filtered_list, char *content, t_shell *sh)
{
	t_list	*new_node;
	t_list	*tmp;

	new_node = safe_calloc(1, sizeof(t_list), PROMPT, sh);
	new_node->content = content;
	new_node->next = NULL;
	if (!filtered_list)
		return (new_node);
	tmp = filtered_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (filtered_list);
}

t_list	*pattern_filter(t_list *files, t_exp *exp, t_shell *sh)
{
	t_list	*current;
	char	*full_filename;
	t_list	*filtered_list;

	filtered_list = NULL;
	current = files;
	while (current)
	{
		full_filename = (char *)current->content;
		if (pattern_match(full_filename, exp->buf, 0, exp)
			&& !not_explicit_hidden_file(full_filename, exp))
			filtered_list = add_filtered_node(filtered_list, full_filename, sh);
		current = current->next;
	}
	return (filtered_list);
}
