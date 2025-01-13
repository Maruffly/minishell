#ifndef LIBRARIES_H
# define LIBRARIES_H


# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <sys/ioctl.h>


# include "../libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <curses.h>

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

#endif
