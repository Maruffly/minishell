/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:52:06 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:29:09 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_preset_bin_path(char *bin_path, t_shell *sh)
{
	struct stat	path_stat;

	if (access(bin_path, X_OK) == -1)
	{
		if (errno == EACCES)
			error("Permission denied", bin_path, 126, sh);
		else if (errno == ENOENT)
			error("No such file or directory", bin_path, 127, sh);
		else
			error_handler(bin_path, errno, sh);
	}
	stat_s(bin_path, &path_stat, sh);
	if (S_ISDIR(path_stat.st_mode))
		error("is a directory", bin_path, 126, sh);
	return (bin_path);
}

static char	*find_bin_path(char *bin_name, t_shell *sh)
{
	char	*bin_path;
	bool	permission_denied;
	char	**paths_array;

	paths_array = build_paths_array(sh);
	if (!paths_array)
		error("command not found", bin_name, 127, sh);
	permission_denied = false;
	while (*paths_array)
	{
		bin_path = join_path(*paths_array, bin_name, sh);
		if (access(bin_path, X_OK) == EXIT_SUCCESS)
			return (bin_path);
		else if (errno == EACCES)
			permission_denied = true;
		else if (errno != ENOENT)
			error_handler("access", errno, sh);
		paths_array++;
	}
	if (permission_denied)
		error("Permission denied", bin_name, 126, sh);
	else
		error("command not found", bin_name, 127, sh);
	return (NULL);
}

char	*get_bin_path(char *bin, t_shell *sh)
{
	if (ft_strncmp(bin, "", 1) == 0)
		error("command not found", bin, 127, sh);
	else if (ft_strchr(bin, '/'))
		return (check_preset_bin_path(bin, sh));
	else if (ft_strncmp(bin, ".", 1) == 0 || ft_strncmp(bin, "..", 2) == 0)
		error("command not found", bin, 127, sh);
	else
		return (find_bin_path(bin, sh));
	return (NULL);
}
