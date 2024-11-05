# define MINISHELL_H
#  ifndef MISNISHELL_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

// Macros
# define RESET	"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELL	"\e[33m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"


typedef enum s_token
{
	ARG,
	CMD,
	INFILE, 
	OUTFILE, 
	HEREDOC,
	LIMITER, 
	APPEND, // >>
	TRUNCATE, // >
	PIPE, // |
	READ_FROM, // <
}	t_token;

void	read_line(void);

#endif
