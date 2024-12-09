/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:35:41 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/09 13:55:20 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libraries.h"

extern sig_atomic_t	g_signal_value;

typedef enum e_token_type
{
	OR, /* || */
	AND, /* && */
	PAR, /* () */
	ARG,
	CMD,
	PIPE, /* | */
	WORD,
	ERROR,
	INFILE,
	OUTFILE,
	HEREDOC, /* << */
	LIMITER,
	WILDCARD,
	APPEND_OUT, /* >> */
	REDIRECT_IN, /* < */
	REDIRECT_OUT, /* > */
	OPEN_PARENTHESIS, /* ( */
	CLOSE_PARENTHESIS, /* ) */
}	t_token_type;

typedef enum e_prompt_mode
{
	MAIN_PROMPT,
	HEREDOC_PROMPT,
}			t_prompt_mode;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env_list
{
	struct s_env_list	*head;
	struct s_env_list	*next;
	char				*var_name;
	char				*var_value;
}	t_env_list;

typedef struct s_shell
{
	t_env_list			*env;
	char				*home;
	/* t_list			*allocated_pointers[3]; */
	char				*parsing_error;
	bool				is_parent;
	int					last_status;
}	t_shell;

typedef struct	s_command
{
	char				**args;
	char				*command;
	int					exit_code;
	int					input_fd;
	int					output_fd;
	char				*infile;
	char				*outfile;
	bool				append_mode;
	bool				heredoc_mode;
	char				*heredoc_limiter;
	char				logical_operator;
	t_token_type		type;
	bool				error;
	struct s_command	*next;
}	t_command;

typedef struct	s_ast
{
	t_token_type	type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

#endif

