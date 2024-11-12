# ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"
# include "parsing.h"
# include "builtins.h"

// token_words.c
int		is_quote(char c);
int		is_blank(char c);
int		is_NULL(char *line);
int		is_word(t_env_list *env, char *line, int i);
int		is_variable(t_env_list *env, char *line, int i);

// token_redirections.c
int		is_heredoc(char *line, int i);
int		is_redirection(char *line, int i);
int		is_input_chevrons(char *line, int i);
int		is_output_chevrons(char *line, int i);
int		is_append_chevrons(char *line, int i);

// token_operators.c
int		is_pipe(char *line, int i);
int		is_separator(char *line, int i);
int		is_or_operator(char *line, int i);
int		is_and_operator(char *line, int i);
int		is_boolean_operator(char *line, int i);

// token_specials.c
int		is_special_char(char c);
int		is_parenthesis(char *line, int i);
int		is_escaped_char(char *line, int i);
int		is_open_paranthesis(char *line, int i);
int 	is_close_paranthesis(char *line, int i);

// token_utils.c
bool	is_special_operator(char c);
t_token	identify_token_type(char *token);
char	*extract_word(char *line, int pos);
char	*get_next_token(char *line, int pos);
void	skip_whitespace(char *line, int *pos);

// token commands
int		is_cmd(char *word);
int		is_builtin(char *word);
void	ft_free_split(char **array);
int		check_full_path(char *path, char *word);

#endif