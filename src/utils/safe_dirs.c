/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:11:45 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 11:40:58 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct dirent	*safe_readdir(DIR *dirp, t_shell *sh)
{
	struct dirent	*ret;

	errno = 0;
	ret = readdir(dirp);
	if (!ret && errno != 0)
		error_handler("readdir", errno, sh);
	return (ret);
}

int	safe_closedir(DIR *dirp, t_shell *sh)
{
	int	ret;

	errno = 0;
	ret = closedir(dirp);
	if (ret == -1 && errno != 0)
		error_handler("closedir", errno, sh);
	return (ret);
}

DIR	*safe_opendir(char *name, t_shell *sh)
{
	DIR	*ret;

	errno = 0;
	ret = opendir(name);
	if (!ret && errno != 0)
		error_handler("opendir", errno, sh);
	return (ret);
}
