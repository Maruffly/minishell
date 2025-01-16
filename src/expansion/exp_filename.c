/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:17:13 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/15 17:12:43 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	filename_expansion(t_expand *exp, t_shell *sh)
{
	t_token	*files;

	(void)sh;
	if (!exp || !sh)
		return ;
	exp->buf[exp->buf_i] = '\0';
	files = get_files_list(exp, sh);
	if (!files)
		return ;
	files = pattern_filter(files, exp);
	if (files)
	{
		list_of_file_to_token_list(files, exp, sh);
		exp->buf_i = 0;
		exp->buf[exp->buf_i] = '\0';
	}
}

t_token	*get_files_list(t_expand *exp, t_shell *sh)
{
	DIR				*dir;
	char			*path;
	t_token			*files;
	char			*full_name;
	struct dirent	*entry;

	if (!exp || !sh)
		return (NULL);
	files = NULL;
	full_name = NULL;
	path = extract_root_path(exp, sh);
	dir = opendir(path);
	if (!dir)
	{
		free(path);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		full_name = ft_strdup(entry->d_name);
		if (!full_name)
		{
			closedir(dir);
			free(path);
			return (NULL);
		}
		if (ft_strcmp(path, "."))
			full_name = ft_strjoin(path, full_name);
		entry = readdir(dir);
	}
	closedir(dir);
	free(path);
	return (files);
}
