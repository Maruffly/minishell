/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:40:18 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/28 14:28:11 by jlaine           ###   ########.fr       */
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
	char	*full_filename;
	
	if (!tokens)
		return (NULL);
	cur = tokens;
	while (cur)
	{
		full_filename = (char *)cur->value;
		if (!pattern_match(full_filename, exp->buf, 0))
		{
			next = cur->next;
			remove_list_node(&cur, &tokens, NULL, false);
			cur = next;
		}
		else
			cur = cur->next;
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

bool pattern_match(char *filename, char *pattern, int i)
{
	if (!pattern[i])
		return (!filename[0]);
	if (pattern[i] == '*')
	{
		return (pattern_match(filename, pattern, i + 1) ||
				(filename[0] && pattern_match(filename + 1, pattern, i)));
	}
	if (!filename[0])
		return (false);
		
	if (pattern[i] == '?' || pattern[i] == filename[0])
		return pattern_match(filename + 1, pattern, i + 1);
	return (false);
}

void	insert_ordered(t_token **head, t_token *new_node, t_shell *sh)
{
	t_token	*current;

	(void)sh;
	if (!*head || ft_strcmp((*head)->value, new_node->value) >= 0)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next && ft_strcmp(current->next->value, new_node->value) < 0)
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
}
