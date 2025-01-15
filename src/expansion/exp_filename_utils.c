/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:40:18 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/15 17:52:25 by jlaine           ###   ########.fr       */
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
	t_token	*current;
	t_token	*next;
	char	*full_filename;
	(void)next;
	(void)exp;

	if (!tokens || !exp)
		return (NULL);
	current = tokens;
	while (current)
	{
		full_filename = (char *)current->value;
		if (!pattern_match(full_filename, exp->buf, 0, exp))
		{
			next = current->next;
			remove_list_node(&current, &tokens, NULL, false);
			current = next;
		}
		else
			current = current->next;
	}
	return (tokens);
}

void	list_of_file_to_token_list(t_token *tokens, t_expand *exp, t_shell *sh)
{
	if (!tokens || !exp || !sh)
		return ;
	while (tokens)
	{
		if (!add_token_to_list(exp, sh))
		{
			error("expansion", "failed to add token to list", EXIT_FAILURE, sh);
			return ;
		}
		tokens = tokens->next;
	}
}

// Check if current char is wildcard that need to be expanded
bool	is_active_wildcard(int i, t_expand *exp)
{
	t_token	*current;

	if (!exp || !exp->wildcards_position)
		return (false);
	current = exp->wildcards_position;
	while (current)
	{
		if (*((int *)(current->value)) == i)
			return (true);
		current = current->next;
	}
	return (false);
}

// check if the end of a pattern is only active wildcards
bool	only_active_wildcard_left(char *str, t_expand *exp)
{
	if (!str || !*str || !exp)
		return (false);
	while (*str)
	{
		if (*str != '*' || !is_active_wildcard(exp->buf_i, exp))
			return (false);
		str++;
	}
	return (true);
}

bool	pattern_match(char *filename, char *pattern, int pattern_index,
		t_expand *exp)
{
	if (!filename || !pattern || !exp)
		return (false);
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
