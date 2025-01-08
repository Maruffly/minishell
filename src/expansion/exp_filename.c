/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:17:13 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/08 13:44:48 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	filename_expansion(t_expand *exp, t_shell *sh)
{
	t_token	*files;

	(void)sh;
	exp->buf[exp->buf_i] = '\0';
	files = get_files_list(exp, sh);
	files = pattern_filter(files, exp);
	if (files)
	{
		list_of_file_to_token_list(files, exp, sh); ///// TO DO
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

	files = NULL;
	full_name = NULL;
	path = extract_root_path(exp, sh);
	dir = opendir(path);
	if (dir)
	{
		entry = readdir(dir);
		while (entry)
		{
			full_name = ft_strdup(entry->d_name);
			if (ft_strcmp(path, "."))
				full_name = ft_strjoin(path, full_name);
			// if (ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, ".."))
			// 	lst_ordered(full_name, &files, sh);
			entry = readdir(dir);
		}
		closedir(dir);
	}
	return (files);
}
