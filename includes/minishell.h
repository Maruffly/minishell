/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/15 10:13:35 by jlaine           ###   ########.fr       */
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

// print
void 			print_ast(t_ast *node);

// signal //
void		set_signal(int signum, void (*handler)(int));
void		set_main_signals(void);
void		set_heredoc_signals(void);
void		set_exec_signals(void);
void		set_child_signals(void);
void		handle_eof(char *input, t_shell *sh);

// readline //
char			*read_line(t_prompt_mode mode);

// INIT COMMAND STRUCT //

// EXIT //
void			exit_shell(int exit_status, t_shell *sh);
void			free_ast(t_ast *node);
void			free_token_list(t_token *tokens);
void			handle_exit_status(char *input, int *exit_code);
void			error(char *context, char *description, int exit_status,
				t_shell *sh);
void 			ft_lstclear_env(t_env_list **lst, void (*del)(void *));
void 			ft_lstdelone_env(t_env_list *env, void (*del)(void *));
void			remove_list_node(t_token **node, t_token **head, 
				void (*free_function)(void *), bool free_node);
void			free_env_array(char **envp);


// errors
int				report_syntax_error(t_shell *sh);
void			*syntax_error(char *unexpected_token, t_shell *sh);

// token_type.c
int				is_blank(char c);
int				is_builtin(char *word);
bool			is_word(t_token *token);
bool			is_redirect(t_token *token);
bool			is_special_operator(char c);
bool			is_operator(t_token *token);
bool			is_open_parenthesis(t_token *token);
bool			is_close_parenthesis(t_token *token);

// token utils.c
char			*get_token_string(t_token_type type);
void			skip_whitespace(char *line, int *pos);
void			ft_lstadd_back_token(t_token **token_list, t_token *new_token);
void			ft_lstclear_token(t_token **lst, void (*del)(void *));
void			ft_lstdelone_token(t_token *lst, void (*del)(void *));
int				ft_lstsize_token(t_token *token);
void			add_front_token(t_token **token_list, t_ast *node, t_shell *sh);



// lexer // find token type // create token
int				lexer(char *input, t_token **token_list, t_shell *sh);
t_token_type	get_next_token(char *input, int *len, t_shell *sh);
t_token_type	get_pipe_logic(char *input, char c, int *len, t_shell *sh);
t_token_type	get_redirect(char *input, char c, int *len, t_shell *sh);
t_token_type	get_subshell(char *input, int *len);
t_token_type	get_word(char *input, char c, int *len, t_shell *sh);
t_token			*create_token(t_token_type type, char *input, size_t len);

// parsing.c
t_ast			*parse_command(t_token **token);
t_ast			*parse_subshell(t_token **token, t_shell *sh);
t_ast			*parse_logical(t_token **token, t_shell *sh);
int				parser(t_token *token, t_ast **ast, t_shell *sh);
t_ast			*parse_pipe(t_token **token, t_shell *sh);
t_ast			*parse_redirection(t_token **token, t_shell *sh);
t_ast			*parse_redirection_list(t_token **token, t_ast *command, t_shell *sh);

// parsing utils
void			add_char_to_value(char **value, char c);
void			add_arg_tab(char ***array, char *new_arg);

// create ast
void			init_ast_node(t_ast **node, t_ast_type type);
t_ast			*create_ast_cmd(char **args);
t_ast			*create_ast_subshell(t_ast *child, t_shell *sh);
t_ast			*create_ast_redirection(t_token_type direction, t_token *filename,
				t_ast *command, t_shell *sh);
t_ast			*create_ast_pipeline(t_ast	*left, t_ast *right, t_shell *sh);
t_ast			*create_ast_logical(t_ast *left, t_token_type op, t_ast *right, t_shell *sh);

// expansion.c
// void			handle_expansion(char *input, int *pos, char **value,
// 								t_env_list *env_list, int exit_status);
// char			*expand_exit_status(int *pos, int exit_status);
void			add_expanded_value(char **value, char *expanded_value);
// char			*expand_env_variable(char *input, int *pos, t_env_list *env_list);
void			handle_redirection(char *input, int *pos, char **value);

// quotes.c
int				is_quoted(char *str);
void 			remove_quotes(char *str);
void			add_char_to_value(char **value, char c);
void			handle_quotes(char *input, int *pos, char **value);
int				dup_value(t_token *cur, char **args, int count);

// handle_tokens.c
t_token			*free_token_value(char *value);
void			*handle_all_tokens(char *input, int *pos, char **value,
				t_env_list *env_list, int exit_status);
char			*handle_parentheses(char *input, int *pos);

// ast_utils.c
t_ast			*ast_from_tokens(t_token *tokens);

// redirections
t_ast			*build_redir_cmd(t_ast *prefix, t_ast *suffix, t_ast *command);

// HEREDOC //
void			free_heredoc(t_heredoc *hdoc);

// EXEC HEREDOC//
int				execute_heredoc(t_ast *ast, t_shell *sh);
int 			heredoc_eof_handler(t_heredoc *hdoc);

/* void	redir_command(t_command *cmd);
void	close_unused_fds(t_command	*cmd);
void	setup_pipes(t_command *cmd);
int		update_prev_output_fd(t_command *cmd);
void	execute_command(t_command *cmd, t_env_list *env, int prev_output_fd);
 */
// ENV
char 			*get_current_path(t_env_list *list);
t_env_list		*init_env_list(void);
void			free_env_list(void *list);
void			print_env_list(t_env_list *list);
void			update_env_node(t_env_list *list, char *var_name, char *var_value);
void			add_env_node(t_env_list *list, char *var_name, char *var_value);
void			remove_env_node(t_env_list *list, char *var_name);
t_env_list		*find_env_node(t_env_list *list, char *name);
void			update_pwd_env(t_env_list *env_list, char *old_pwd);
int				is_valid_var_name(char *name);
t_env_list		*init_envp(char **envp);
char			**list_to_envp(t_env_list *env);
void			check_env_path(char **envp);
t_env_list		*find_env_token(char *name, t_env_list *env_tokens);


// BUILTINS
void			exec_echo(t_ast_command *cmd);
void			exec_cd(t_ast_command *cmd, t_env_list *env_list);
void			exec_echo(t_ast_command *cmd);
void			exec_env(t_env_list *env_list);
void			exec_exit(t_ast_command *cmd);
void			exec_export(t_env_list *env_list, t_ast_command *cmd);
void			exec_exit(t_ast_command *cmd);
void			exec_export(t_env_list *env_list, t_ast_command *cmd);
void			exec_pwd(void);
void			exec_unset(t_env_list *env_list, t_ast_command *cmd);
void			exec_unset(t_env_list *env_list, t_ast_command *cmd);


// EXPANSION
t_ast			*node_expansion(t_ast *node, t_shell *sh);
void			command_expansion(t_ast *node, t_shell *sh);
void			redirection_expansion(t_ast *node, t_shell *sh);
void			arg_expansion(char *str, t_token **expanded_args, t_shell *sh);
bool			init_expansion(t_expand *exp, char *str, t_token **expanded_args, 
						t_shell *sh);
void			no_quote(char *str, t_expand *exp, t_shell *sh);
void			single_quote(char *str, t_expand *exp);
void			double_quote(char *str, t_expand *exp, t_shell *sh);
void			*add_token_to_list(t_expand *exp, t_shell *sh);
void			add_var_to_buffer(char *value, t_expand *exp, t_shell *sh);
void			expand_var(char *str, t_expand *exp, t_shell *sh);
void			expand_last_status(t_expand *exp, t_shell *sh);
char			*expand_heredoc_vars(char *line, t_shell *sh, t_expand *exp);
char			*get_valid_name(char *str, t_expand *exp, t_shell *sh);
char			**list_to_array(t_token **lst, t_shell *sh);
void			add_wildcard_pos(t_token **token_list, int pos, t_shell *sh);
void			save_wildcards_pos(char *to_check, t_expand *exp, t_shell *sh);
void			filename_expansion(t_expand *exp, t_shell *sh);
t_token			*get_files_list(t_expand *exp, t_shell *sh);
char			*extract_root_path(t_expand *exp, t_shell *sh);
t_token			*pattern_filter(t_token *tokens, t_expand *exp);
char			*expand_env_var(char *str, t_expand *exp, t_shell *sh);
char			*word_splitting(t_expand *exp, char *value, t_shell *sh);
void			list_of_file_to_token_list(t_token *tokens, t_expand *exp, t_shell *sh);
bool			pattern_match(char *filename, char *pattern, int pattern_index,
				t_expand *exp);
bool			is_active_wildcard(int i, t_expand *exp);
bool			only_active_wildcard_left(char *str, t_expand *exp);


// EXEC
int				execute(t_ast *node, t_exit end, t_shell *sh);
int				check_process_child_exit(int status, bool *new_line, t_shell *sh);


// EXEC LOGICAL
int 			exec_logical(t_ast_logical *logical, t_shell *sh);

// EXEC PIPELINE
int				exec_pipeline(t_ast *node, t_shell *sh);
t_token 		*build_cmd_list(t_ast *node, t_shell *sh);
int 			execute_pipeline_token(t_token *pipeline, t_shell *sh);
pid_t			exec_one_pipeline_token(t_token *pipeline, int prev_read_end, int p[2],
				t_shell *sh);
void			setup_for_next_command(int *prev_read_end, int p[2], t_shell *sh);
int				wait_for_children(pid_t last_pid, int n_pipeline, t_shell *sh);

// EXEC REDIRECTION
int				redirect_input(t_ast_redirection *redir, t_shell *sh);
int				redirect_output(t_ast_redirection *redir, t_shell *sh);
int				append_output(t_ast_redirection *redir, t_shell *sh);
int				exec_redirection(t_ast_redirection *redir, t_shell *sh);

// EXEC SUBSHELL
int				exec_subshell(t_ast_subshell *subshell, t_shell *sh);

// EXEC COMMAND
void			exec_extern_command(t_ast_command *cmd, t_shell *sh);
int				fork_command(t_ast_command *cmd, t_exit end, t_shell *sh);
int				exec_command(t_ast_command *cmd, t_exit end, t_shell *sh);
char			**convert_env_list_to_array(t_env_list *env_list);
char			*find_command_path(char *command, t_env_list *env);
char			*search_in_path(char *command, t_env_list *env);
char			*get_path_env(t_env_list *env);
char			*build_path(char *dir, char *command);


char *clean_command(char *cmd);




#endif
