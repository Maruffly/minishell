/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:13:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/18 20:34:41 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
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

typedef struct	s_command
{
	char				**args;
	int					input_fd;
	int					output_fd;
	t_token				type;
	struct s_command	*next;
}	t_command;

t_command	*init_command(void);
t_command	*parse_input(char *input);
void		free_cmd_list(t_command *cmd);
void		add_command(t_command **head, t_command *new_cmd);
char		**ft_add_to_array(char **array, char *new_element);

#endif
