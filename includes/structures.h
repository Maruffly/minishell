/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:35:41 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/01/27 14:19:26 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libraries.h"

extern sig_atomic_t	g_signal_value;

typedef enum e_token_type
{
	OR,					/* 0 */
	AND,				/* 1 */
	PAR,				/* 2 */
	PIPE,				/* 3 */
	WORD,				/* 4 */
	ERROR,				/* 5 */
	INFILE,				/* 6 */
	OUTFILE,			/* 7 */
	HEREDOC,			/* 8 */
	WILDCARD,			/* 9 */
	APPEND_OUT,			/* 10 */
	REDIRECT_IN,		/* 11 */
	REDIRECT_OUT,		/* 12 */
	OPEN_PARENTHESIS,	/* 13 */
	CLOSE_PARENTHESIS,	/* 14 */
}	t_token_type;

typedef enum e_prompt_mode
{
	MAIN_PROMPT,
	HEREDOC_PROMPT,
}							t_prompt_mode;

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_SUBSHELL,
	AST_LOGICAL,
	AST_PIPELINE,
	AST_REDIRECTION,
	AST_SYNTAX_ERROR

}							t_ast_type;

typedef struct s_ast_command
{
	char					**args;
}							t_ast_command;

typedef struct s_ast_pipeline
{
	struct s_ast			*left;
	struct s_ast			*right;
}							t_ast_pipeline;

typedef struct s_ast_logical
{
	t_token_type			operator;
	struct s_ast			*left;
	struct s_ast			*right;
}							t_ast_logical;

typedef struct s_ast_redirection
{
	t_token_type			direction;
	struct s_ast			*command;
	char					*file;
	int						heredoc_fd;
}							t_ast_redirection;

typedef struct s_ast_subshell
{
	struct s_ast			*child;
}							t_ast_subshell;

typedef struct s_ast_syntax_error
{
	char					*unexpected_token;
}							t_ast_syntax_error;

typedef struct s_ast
{
	t_ast_type				type;
	union
	{
		t_ast_command		command;
		t_ast_pipeline		pipeline;
		t_ast_logical		logical;
		t_ast_redirection	redirection;
		t_ast_subshell		subshell;
		t_ast_syntax_error	s_error;
	} u_data;
}							t_ast;

typedef struct	s_heredoc
{
	int					pipe_fd[2];
	char				buffer[1024];
	ssize_t				bytes_read;
	char				*limiter;
	int					expand_vars;
	int					saved_stdout;
	size_t				content_size;
	pid_t				heredoc_pid;
}	t_heredoc;

typedef struct s_token
{
	t_ast			*node;
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
	t_prompt_mode		prompt_mode;
	char				*home;
	/* t_list			*allocated_pointers[3]; */
	char				*parsing_error;
	bool				is_parent;
	int					last_status;
}	t_shell;

typedef enum	e_quote
{
	NO_QUOTE,
	IN_DOUBLE_QUOTE,
	IN_SINGLE_QUOTE,
}	t_quote;

typedef struct s_wildcard
{
	int					position;
	struct s_wildcard	*next;
}	t_wildcard;

typedef struct s_expand
{
	int			i;
	char		*buf;
	int			buf_i;
	bool		has_match;
	t_quote		context;
	int			buf_size;
	t_token		**tokens;
	bool		empty_quotes;
	t_wildcard	*wildcards_position;
}	t_expand;

typedef struct s_var
{
	char		*name;
	char		*value;
	size_t		len;
}	t_var;


typedef enum e_exit
{
	KEEP_RUNNING, 
	EXIT_SHELL
}	t_exit;




#endif

