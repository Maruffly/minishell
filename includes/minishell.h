/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:35:41 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 12:20:34 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structures.h"

# define RESET	"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELL	"\e[33m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

// UTILS
int				count_args(char **argv);
void			add_arg_to_array(char ***array, char *new_arg, t_shell *sh);

// PARSER UTILS
t_token_type	type(t_list *token);
bool			is_valid_name(char *name);
char			*type_to_string(t_token_type type);
bool			is_type(t_list **token_list, int num_args, ...);

// CLEANING
void			free_env_var(void *content);
void			remove_list_node(t_list **node, t_list **head,
					void (*free_function)(void *), bool free_node);

// MAIN
int				main_loop(t_shell *sh);
void			clear_prompt(t_shell *sh);
char			*get_prompt(t_prompt_mode mode);
void			shell_init(t_shell *sh, char **env);
void			exit_shell(int exit_status, t_shell *sh);

// ERRORS
int				report_syntax_error(t_shell *sh);
int				report_errno(char *context, t_shell *sh);
void			error_handler(char *context, int errnum, t_shell *sh);	
void			*set_syntax_error(char *unexpected_token, t_shell *sh);
void			report_name_error(char *assignment, bool *name_error,
					t_shell *sh);
int				report_error(char *context, char *element, char *description,
					t_shell *sh);
void			error(char *context, char *description, int exit_status,
					t_shell *sh);

// ENV
char			*name(t_list *env);
char			*value(t_list *env);
char			**env_to_char_array(t_shell *sh);
t_list			*env_var(char *name, t_list *env);
t_list			*init_env(char **env, t_shell *sh);
int				print_env(bool export_format, t_list *env, t_shell *sh);
void			add_new_env_var(char *name, char *value, t_list **list,
					t_shell *sh);
void			edit_env_value(t_list *in_env, char *new_value, bool add,
					t_shell *sh);

// BUILTINS
int				exec_cd(t_ast_command *cmd, t_shell *sh);
int				exec_pwd(t_ast_command *cmd, t_shell *sh);
int				exec_env(t_ast_command *cmd, t_shell *sh);
int				exec_echo(t_ast_command *cmd, t_shell *sh);
int				exec_exit(t_ast_command *cmd, t_shell *sh);
int				exec_unset(t_ast_command *cmd, t_shell *sh);
int				exec_export(t_ast_command *cmd, t_shell *sh);

// TOKEN
int				is_space(int c);
int				is_token(int c);
int				lexer(char *input, t_list **token_list, t_shell *sh);
t_token			*create_token(t_token_type type, char *value, size_t len,
					t_shell *sh);
t_token_type	get_subshell(char *input, size_t *len);
t_token_type	get_next_token(char *input, size_t *len, t_shell *sh);
t_token_type	get_logic_and_pipe(char *input, char c, size_t *len,
					t_shell *sh);
t_token_type	get_redirect(char *input, char c, size_t *len, t_shell *sh);
t_token_type	get_word(char *input, size_t *len, t_shell *sh);

// AST
void			init_ast_node(t_ast **node, t_ast_type type, t_shell *sh);
t_ast			*create_ast_command(char **argv, t_shell *sh);
t_ast			*create_ast_subshell(t_ast *child, t_shell *sh);
t_ast			*create_ast_pipeline(t_ast *left, t_ast *right, t_shell *sh);
t_ast			*create_ast_logical(t_ast *left, t_token_type operator,
					t_ast *right, t_shell *sh);
t_ast			*create_ast_redirection(t_token_type direction,
					t_list *filename, t_ast *child, t_shell *sh);

// PARSER
int				parser(t_list *token_list, t_ast **ast, t_shell *sh);
t_ast			*parse_subshell(t_list **token, t_shell *sh);
t_ast			*parse_redirection(t_list **token, t_shell *sh);
t_ast			*parse_command(t_list **token, t_shell *sh);
t_ast			*parse_logical(t_list **token, t_shell *sh);
t_ast			*parse_pipeline(t_list **token, t_shell *sh);
t_ast			*build_redirected_command(t_ast *prefix, t_ast *suffix,
					t_ast *command);
t_ast			*parse_redirection_list(t_list **token, t_ast *command,
					t_shell *sh);

// EXEC
char			**build_paths_array(t_shell *sh);
t_builtin_func	get_builtin_function(char *cmd_name);
char			*get_bin_path(char *bin, t_shell *sh);
int				exec_pipeline(t_ast *node, t_shell *sh);
int				execute_heredocs(t_ast *node, t_shell *sh);
int				exec_redir(t_ast_redirection *redir, t_shell *sh);
char			*join_path(char *path_to, char *file, t_shell *sh);
int				execute(t_ast *node, t_execute_end end, t_shell *sh);
int				exec_subshell(t_ast_subshell *subshell, t_shell *sh);
int				exec_cmd(t_ast_command *cmd, t_execute_end end, t_shell *sh);
int				wait_for_children(pid_t last_pid, int n_pipeline, t_shell *sh);
int				fork_command(t_ast_command *cmd, t_execute_end end,
					t_shell *sh);
int				execute_logical(t_ast_logical *logical, t_shell *sh);
void			setup_for_next_command(int *prev_read_end, int p[2],
					t_shell *sh);
int				check_process_child_exit(int status, bool *new_line,
					t_shell *sh);

// EXPANSION
bool			is_active_wildcard(int i, t_exp *exp);
t_ast			*expand_node(t_ast *node, t_shell *sh);
void			expand_command(t_ast *node, t_shell *sh);
t_list			*pattern_filter(t_list *files, t_exp *exp);
char			*extract_root_path(t_exp *exp, t_shell *sh);
void			filename_expansion(t_exp *exp, t_shell *sh);
void			expand_last_status(t_exp *exp, t_shell *sh);
void			*add_token_to_list(t_exp *exp, t_shell *sh);
void			expand_redirection(t_ast *node, t_shell *sh);
void			expand_var(char *str, t_exp *exp, t_shell *sh);
void			expand_tilde(char *str, t_exp *exp, t_shell *sh);
char			**convert_list_to_array(t_list **lst, t_shell *sh);
char			*expand_env_var(char *str, t_exp *exp, t_shell *sh);
char			*word_splitting(t_exp *exp, char *value, t_shell *sh);
bool			only_active_wildcard_left(const char *str, t_exp *exp);
void			add_variable_to_buffer(char *value, t_exp *exp, t_shell *sh);
void			exp_single_arg(char *str, t_list **expanded_args, t_shell *sh);
bool			not_explicit_hidden_file(const char *full_filename,
					t_exp *exp);

bool			pattern_match(const char *filename, const char *pattern,
					int pattern_index, t_exp *exp);
void			list_of_file_to_token_list(t_list *lst, t_exp *exp,
					t_shell *sh);
void			init_exp(t_exp *exp, char *str, t_list **expanded_args,
					t_shell *sh);
void			saved_wildcards_position(char *to_check, t_exp *exp,
					t_shell *sh);

// SIGNALS
void			sigint_prompt(int signum);
void			sigint_heredoc(int signum);
void			set_signal_prompt(void);
void			set_signal_main_process(void);
void			set_signal_child_process(void);
void			set_signal_heredoc(void);

// SAFE
pid_t			safe_fork(t_shell *sh);
int				safe_close(int fd, t_shell *sh);
pid_t			safe_wait(int *wstatus, t_shell *sh);
int				safe_pipe(int pipefd[2], t_shell *sh);
int				safe_closedir(DIR *dirp, t_shell *sh);
struct dirent	*safe_readdir(DIR *dirp, t_shell *sh);
int				safe_dup2(int oldfd, int newfd, t_shell *sh);
DIR				*safe_opendir(char *name, t_shell *sh);
void			check_node_alloc(t_list *new_node, void *pointer, t_shell *sh);
void			track_alloc(void *pointer, t_tracking_scope scope, t_shell *sh);
void			*safe_alloc(void *pointer, t_tracking_scope scope, t_shell *sh);
int				safe_execve(const char *pathname, char *const argv[],
					char *const envp[], t_shell *sh);
char			*safe_strdup(char *s1, t_tracking_scope scope,
					t_shell *sh);
char			**safe_split(char *s, char c, t_tracking_scope scope,
					t_shell *sh);
int				safe_open(char *pathname, int flags, mode_t mode, t_shell *sh);
char			*safe_strjoin(char *s1, char *s2,
					t_tracking_scope scope, t_shell *sh);
void			safe_lst_addfront(void *content, t_list **lst,
					t_tracking_scope scope, t_shell *sh);
void			safe_lst_addback(void *content, t_list **lst,
					t_tracking_scope scope, t_shell *sh);
int				safe_stat(const char *restrict path, struct stat *restrict buf,
					t_shell *sh);
void			*safe_calloc(size_t count, size_t size, t_tracking_scope scope,
					t_shell *sh);

#endif
