/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:13:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/21 16:06:47 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H

# define TOKEN_BUFFER_SIZE	1024

# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
/* # include "../includes/token.h" */


typedef enum s_token
{
	OR, /* || */
	AND, /* && */
	ARG,
	CMD,
	PIPE, /* | */
	INFILE,
	OUTFILE,
	HEREDOC, /* << */
	LIMITER,
	APPEND_OUT, /* >> */
	REDIRECT_IN, /* < */
	REDIRECT_OUT, /* > */
}	t_token;

/* typedef struct s_token_list
{
	char				*token;
	struct s_token_list	*next;
}	t_token_list; */

typedef struct	s_command
{
	char				**args;
	int					input_fd;
	int					output_fd;
	char				logical_operator;
	t_token				type;
	struct s_command	*next;
}	t_command;

t_command	*init_command(void);
t_command	*parse_input(char *input);
void		free_cmd_list(t_command *cmd);
void		add_command(t_command **head, t_command *new_cmd);
char		**ft_add_to_array(char **array, char *new_element);

#endif
