/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/04 14:08:33 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef PARSING_H
# define PARSING_H

# define TOKEN_BUFFER_SIZE	1024

# include <stdlib.h>
# include <stdbool.h>
# include <dirent.h>

# include "../libft/libft.h"
# include "./env.h"


typedef enum s_token_type
{
	OR, /* || */
	AND, /* && */
	PAR, /* () */
	ARG,
	CMD,
	PIPE, /* | */
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

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/* typedef struct s_token_list
{
	char				*token;
	struct s_token_list	*next;
}	t_token_list; */

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

t_command	*init_command(void);

// parsing.c
t_command	*parse_tokens(t_token *tokens);
char		**token_to_args(t_token *tokens, t_token *stop_token);
void		add_argument_to_command(t_command *cmd, char *arg);
void		add_char_to_value(char **value, char c);
t_token		*create_token(char *input, int *pos, t_env_list *env_list, int exit_status, bool *is_first_token);
t_command	*parse_input(char *input, t_env_list *env_list, int exit_status);
t_token		*tokenize_input(char *input, t_env_list *env_list,
							int exit_status);


// parsing_utils.c
t_command	*init_command(void);
bool		is_metachar(char c);
t_token		*init_token(char *value, t_token_type type);
void		add_token(t_token **head, t_token *new_token);
bool		is_syntax_ok(t_token *new_token, t_token *head);
void		add_command(t_command **head, t_command *new_cmd);
bool		is_blank_line(char *line);
t_command	*handle_error(char *error_message);
int			is_command_ok(t_command *cmd, t_env_list *env_list);
bool		is_empty_line(char *input);




// expansion.c
void		handle_expansion(char *input, int *pos, char **value,
							t_env_list *env_list, int exit_status);
char		*expand_exit_status(int *pos, int exit_status);
void		add_expanded_value(char **value, char *expanded_value);
char		*expand_env_variable(char *input, int *pos, t_env_list *env_list);
void		handle_redirection(char *input, int *pos, char **value);

// quotes.c
void		add_char_to_value(char **value, char c);
void		handle_internal_quotes(char *input, int *pos,
			char **value, char c);
void		handle_quotes(char *input, int *pos, char **value);
void		handle_internal_quotes(char *input, int *pos, char **value, char c);

bool		is_separator(t_token_type type);
int			dup_value(t_token *cur, char **args, int count);


// handle_tokens.c
t_token		*free_token_value(char *value);
void		*handle_all_tokens(char *input, int *pos, char **value,
							t_env_list *env_list, int exit_status);
char		*handle_parentheses(char *input, int *pos);

// ast.c
void		execute_ast(t_ast *node, t_env_list *env, int *exit_code);
void		exec_or_operator(t_ast *node, t_env_list *env, int *exit_code);
void		exec_and_operator(t_ast *node, t_env_list *env, int *exit_code);
void		exec_pipe_cmd(t_ast *node, t_env_list *env, int *exit_code);
void		exec_simple_cmd(t_ast *node, t_env_list *env, int *exit_code);
int			get_last_exit_status(void);
void		set_last_exit_status(int status);



// ast_utils.c
t_command	*ast_to_command(t_ast *node);
t_command	*ast_to_pipeline(t_ast *node);
t_ast		*ast_from_tokens(t_token *tokens);
t_command	*parse_ast_to_commands(t_ast *node);
t_command	*merge_commands(t_command *left, t_command *right, t_token_type operator);


// redirections

bool		handle_redirections(t_token *cur, t_command *cmd);
void		handle_pipeline(t_command **head, t_command **cmd, t_token *start, t_token *stop);
bool		process_redirections(t_token *cur, t_command *cmd, t_command **head);
t_command	*process_pipeline(t_token *cur, t_command *cur_cmd, t_command **head, t_token **start);

#endif
