/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:40:18 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/04 14:01:18 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_root_path(t_expand *exp, t_shell *sh)
{
	int		i;
	char	*path;

	(void)sh;
	if (!exp || !sh)
		return (NULL);
	i = exp->buf_i - 1;
	while (i >= 0 && exp->buf[i] != '/')
		i--;
	if (i == -1)
		return (ft_strdup("."));
	path = ft_calloc(i + 2, sizeof(char));
	if (!path)
		return (NULL);
	ft_strlcpy(path, exp->buf, i + 2);
	return (path);
}

t_token	*pattern_filter(t_token *tokens, t_expand *exp)
{
	t_token	*cur;
	t_token	*next;
	t_token *prev;
	char	*full_filename;

	prev = NULL;
	if (!tokens)
		return (NULL);
	cur = tokens;
	while (cur)
	{
		next = cur->next;
		full_filename = (char *)cur->value;
		if (!pattern_match(full_filename, exp->buf, 0))
			remove_list_node(&cur, &tokens, NULL, false);
		else
			prev = cur;
		cur = next;
	}
	return (tokens);
}

bool is_active_wildcard(int position, t_expand *exp)
{
	t_wildcard	*cur;

	if (!exp || !exp->wildcards_position)
		return (false);
	cur = exp->wildcards_position;
	while (cur)
	{
		if (cur->position == position)
			return (true);
		cur = cur->next;
	}
	return (false);
}

bool pattern_match(char *filename, char *pattern, int f_pos)
{
	int p_pos;
	bool match_rest;

	if (f_pos == 0 && filename[0] == '.' && pattern[0] != '.')
		return (false);
	if (!pattern[f_pos])
		return (!filename[f_pos]);
	if (!filename[f_pos])
		return (!pattern[f_pos] || (pattern[f_pos] == '*' && pattern[f_pos + 1] == '\0'));
	if (pattern[f_pos] == '*')
	{
		p_pos = f_pos + 1;
		if (!pattern[p_pos])
			return (true);
		while (filename[f_pos])
		{
			match_rest = pattern_match(filename + f_pos, pattern + p_pos, 0);
			if (match_rest)
				return (true);
			f_pos++;
		}
		return (pattern_match(filename + f_pos, pattern + p_pos, 0));
	}
	if (pattern[f_pos] == '?' || pattern[f_pos] == filename[f_pos])
		return pattern_match(filename, pattern, f_pos + 1);
		
	return (false);
}
