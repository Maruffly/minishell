/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/03 18:26:30 by jmaruffy         ###   ########.fr       */
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
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			is_first_token;
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

t_command	*init_command(void);

// parsing.c
t_command	*parse_tokens(t_token *tokens);
void		add_char_to_value(char **value, char c);
t_token		*create_token(char *input, int *pos,
			t_env_list *env_list, int exit_status, bool *is_first_token);
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


// expansion.c
void		handle_expansion(char *input, int *pos, char **value,
							t_env_list *env_list, int exit_status);
char		*expand_exit_status(int *pos, int exit_status);
void		add_expanded_value(char **value, char *expanded_value);
char		*expand_env_variable(char *input, int *pos, t_env_list *env_list);


// quotes.c
void		add_char_to_value(char **value, char c);
void		handle_internal_quotes(char *input, int *pos,
			char **value, char c);
void		handle_quotes(char *input, int *pos, char **value);
void		handle_internal_quotes(char *input, int *pos, char **value, char c);

char		**token_to_args(t_token *tokens, t_token *stop_token);
bool		is_separator(t_token_type type);
void 		add_argument_to_command(t_command *cmd, char *arg);

/*
void		add_command(t_command **head, t_command *new_cmd);
char		**ft_add_to_array(char **array, char *new_element);
*/

// redirections

bool		handle_redirections(t_token *cur, t_command *cmd);
void		handle_pipeline(t_command **head, t_command **cmd, t_token *start, t_token *stop);
bool		process_redirections(t_token *cur, t_command *cmd, t_command **head);
t_command	*process_pipeline(t_token *cur, t_command *cur_cmd, t_command **head, t_token **start);

#endif
