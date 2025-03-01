/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:17:13 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 13:55:34 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	lst_insert_ordered(char *to_add, t_list **files, t_shell *sh)
{
	t_list	*tmp;
	t_list	*new_node;

	new_node = ft_lstnew(safe_strdup(to_add, PROMPT, sh));
	check_node_alloc(new_node, to_add, sh);
	track_alloc(new_node, PROMPT, sh);
	if (*files == NULL || ft_strcmp((*files)->content, to_add))
	{
		new_node->next = *files;
		if (*files)
			(*files)->prev = new_node;
		*files = new_node;
	}
	else
	{
		tmp = *files;
		while (tmp->next && ft_strcmp(tmp->next->content, to_add) < 0)
			tmp = tmp->next;
		new_node->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = new_node;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

static t_list	*get_list_of_files(t_exp *exp, t_shell *sh)
{
	t_list			*files;
	char			*path;
	DIR				*dir;
	struct dirent	*entry;
	char			*full_name;

	files = NULL;
	full_name = NULL;
	path = extract_root_path(exp, sh);
	dir = safe_opendir(path, sh);
	if (dir)
	{
		entry = safe_readdir(dir, sh);
		while (entry)
		{
			full_name = safe_strdup(entry->d_name, PROMPT, sh);
			if (ft_strcmp(path, "."))
				full_name = safe_strjoin(path, full_name, PROMPT, sh);
			if (ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, ".."))
				lst_insert_ordered(full_name, &files, sh);
			entry = safe_readdir(dir, sh);
		}
		safe_closedir(dir, sh);
	}
	return (files);
}

void	filename_expansion(t_exp *exp, t_shell *sh)
{
	t_list	*files;

	exp->buf[exp->buf_i] = '\0';
	files = get_list_of_files(exp, sh);
	files = pattern_filter(files, exp, sh);
	if (files)
	{
		list_of_file_to_token_list(files, exp, sh);
		exp->buf_i = 0;
		exp->buf[exp->buf_i] = '\0';
	}
}
