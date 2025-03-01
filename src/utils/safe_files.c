/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:27:00 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 10:56:41 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	safe_close(int fd, t_shell *sh)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		error_handler("close", errno, sh);
	return (ret);
}

int	safe_open(const char *pathname, int flags, mode_t mode, t_shell *sh)
{
	int	ret;

	ret = open(pathname, flags, mode);
	if (ret == -1)
		error_handler(pathname, errno, sh);
	return (ret);
}

int	safe_stat(const char *restrict path, struct stat *restrict buf, t_shell *sh)
{
	int	ret;

	ret = stat(path, buf);
	if (ret == -1)
		error_handler("stat", errno, sh);
	return (ret);
}

int	safe_dup2(int oldfd, int newfd, t_shell *sh)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret == -1)
		error_handler("dup2", errno, sh);
	return (ret);
}
