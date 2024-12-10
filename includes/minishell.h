/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:12:58 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/10 15:35:46 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "structures.h"

// Macros
# define RESET	"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELL	"\e[33m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

// SIGNAL //
void	set_main_signals(void);
void	handle_eof(char *input, t_shell *sh);
void	handle_signal(int signum, void (*handler)(int));


// READ LINE //
char	*read_line(t_prompt_mode mode);

// INIT COMMAND STRUCT //


// EXIT //
void		free_ast(t_ast *node);
void		free_cmd(t_command *cmd);
void		free_pipe(t_command	*pipe);
void	free_cmd_list(t_command *head);
void 	free_token_list(t_token *tokens);
void	handle_exit_status(char *input, int *exit_code);

// errors
int				report_synthax_error(t_shell *sh);
t_token_type	syntax_error(char *unexpected_token, t_shell *sh);

// lexer
int			lexer(char *input, t_token **token_list, t_shell *sh);
void		exit_shell(int exit_status, t_shell *sh);
t_command	*init_command(void);

// token_words.c
int		is_blank(char c);
int		is_NULL(char *line);
int		is_variable(char *line, int i);


// token_specials.c
int				is_special_char(char c);

// token_utils.c
bool			is_special_operator(char c);
t_token_type	get_token_type(char *token, bool *is_first_token);
char			*extract_word(char *line, int pos);
void			skip_whitespace(char *line, int *pos);
void			lst_add_back_token(t_token **token_list, t_token *new_token);
void			ft_lstclear(t_env_list **lst, void (*del)(void *));
void			ft_lstdelone(t_env_list *lst, void (*del)(void *));

// token commands
int				is_builtin(char *word);

// lexer
t_token_type	get_next_token(char *input, int *len, t_shell *sh);
t_token_type	get_pipe_logic_tk(char *input, char c, int *len, t_shell *sh);
t_token_type	get_redirect_tk(char *input, char c, int *len, t_shell *sh);
t_token_type	get_subshell_tk(char *input, int *len);
t_token_type	get_word_tk(char *input, char c, int *len, t_shell *sh);

void			init_command_array(t_command *cmd, char *input);

// parsing.c
char		**token_to_args(t_token *tokens, t_token *stop_token);
void		add_argument_to_command(t_command *cmd, char *arg);
void		add_char_to_value(char **value, char c);

t_token		*create_token(t_token_type type, char *input, size_t len);
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
void		handle_quotes(char *input, int *pos, char **value);

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
t_command	*process_pipeline(t_token *cur, t_command *cur_cmd, t_command **head, t_token **start);

// EXEC //
void	execute_pipeline(t_command *cmd, t_env_list *env);

// CHILD //
char	*get_path(char *cmd, char **envp);
void	redir_command(t_command *cmd);
void	close_unused_fds(t_command	*cmd);
void	setup_pipes(t_command *cmd);
int		update_prev_output_fd(t_command *cmd);
void	execute_command(t_command *cmd, t_env_list *env, int prev_output_fd);

// ENV
char 		*get_current_path(t_env_list *list);
t_env_list	*init_env_list(void);
void		free_env_list(void *list);
void		print_env_list(t_env_list *list);
void		update_env_node(t_env_list *list, char *var_name, char *var_value);
void		add_env_node(t_env_list *list, char *var_name, char *var_value);
void		remove_env_node(t_env_list *list, char *var_name);
t_env_list	*find_env_node(t_env_list *list, char *name);
void		update_pwd_env(t_env_list *env_list, char *old_pwd);
int			is_valid_var_name(char *name);
t_env_list	*init_envp(char **envp);
char		**list_to_envp(t_env_list *env);
void		check_env_path(char **envp);

// BUILTINS
void	exec_cd(t_command *cmd, t_env_list *env_list);
void	exec_echo(t_command *cmd);
void	exec_env(t_env_list *env_list);
void	exec_exit(t_command *cmd);
void	exec_export(t_env_list *env_list, t_command *cmd);
void	exec_pwd(void);
void	exec_unset(t_env_list *env_list, t_command *cmd);

#endif
