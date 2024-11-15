/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:13:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/15 16:47:18 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H

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

#endif
