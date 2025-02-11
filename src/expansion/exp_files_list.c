/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_files_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:29:31 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/11 17:50:37 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static DIR	*initialize_directory(t_expand *exp, t_shell *sh, char **path)
{
	DIR	*dir;

	*path = extract_root_path(exp, sh);
	if (!*path)
		return (NULL);
	dir = opendir(*path);
	if (!dir)
	{
		free(*path);
		return (NULL);
	}
	return (dir);
}

static t_token	*create_file_entry(struct dirent *entry)
{
	char	*full_name;
	t_token	*new_token;

	full_name = ft_strdup(entry->d_name);
	if (!full_name)
		return (NULL);
	new_token = create_token(0, full_name, ft_strlen(full_name));
	if (!new_token)
	{
		free(full_name);
		return (NULL);
	}
	free(full_name);
	return (new_token);
}

static t_token	*process_directory(DIR *dir)
{
	t_token			*files;
	t_token			*new_token;
	struct dirent	*entry;

	files = NULL;
	entry = readdir(dir);
	while (entry)
	{
		new_token = create_file_entry(entry);
		if (!new_token)
		{
			free_token_list(files);
			return (NULL);
		}
		ft_lstadd_back_token(&files, new_token);
		entry = readdir(dir);
	}
	// free_token_list(new_token);
	return (files);
}

t_token	*get_files_list(t_expand *exp, t_shell *sh)
{
	DIR		*dir;
	char	*path;
	t_token	*files;

	path = NULL;
	files = NULL;
	if (!exp || !sh)
		return (NULL);
	dir = initialize_directory(exp, sh, &path);
	if (!dir)
		return (NULL);
	files = process_directory(dir);
	closedir(dir);
	free(path);
	return (files);
}
