#ifndef LIBRARIES_H
# define LIBRARIES_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <limits.h>

# include "../libft/libft.h"

# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

#endif
