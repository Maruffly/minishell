/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libraries.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:48:14 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/29 14:49:54 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARIES_H
# define LIBRARIES_H

# include <term.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

#endif
