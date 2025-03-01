/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:28:32 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 10:57:10 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	safe_fork(t_shell *sh)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
		error_handler("fork", errno, sh);
	return (ret);
}

int	safe_pipe(int pipefd[2], t_shell *sh)
{
	int	ret;

	ret = pipe(pipefd);
	if (ret == -1)
		error_handler("pipe", errno, sh);
	return (ret);
}

pid_t	safe_wait(int *wstatus, t_shell *sh)
{
	pid_t	ret;

	ret = wait(wstatus);
	if (ret == -1)
		error_handler("wait", errno, sh);
	return (ret);
}

int	safe_execve(const char *pathname, char *const argv[], char *const envp[],
	t_shell *sh)
{
	int	ret;

	ret = execve(pathname, argv, envp);
	if (ret == -1)
		error_handler("execve", errno, sh);
	return (ret);
}
