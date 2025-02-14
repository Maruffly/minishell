/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:48:14 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/14 13:13:12 by jlaine           ###   ########.fr       */
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

// MAIN UTILS
void			shell_level(t_shell *sh);
int				launch_shell(t_shell *sh);
char			*read_line(t_prompt_mode mode);
void			init_shell(t_shell *sh, char **envp);

// SIGNAL
void			main_signal(void);
void			set_main_signals(void);
void			set_child_signals(void);
void			set_heredoc_signals(void);
void			sigint_handler(int signum);
void			handle_eof(char *input, t_shell *sh);
void			set_signal(int signum, void (*handler)(int));

// LEXER
bool			should_break(char c, bool in_quote);
t_token_type	get_subshell(char *input, int *len);
t_token_type	get_next_token(char *input, int *len, t_shell *sh);
t_token_type	get_word(char *input, char c, int *len, t_shell *sh);
int				lexer(char *input, t_token **token_list, t_shell *sh);
t_token_type	get_redirect(char *input, char c, int *len, t_shell *sh);
t_token			*create_token(t_token_type type, char *input, size_t len);
t_token_type	get_pipe_logic(char *input, char c, int *len, t_shell *sh);

// HEREDOC
bool			write_to_pipe(int fd, char *line);
void			heredoc_signal_exit(t_heredoc *hdoc);
int				heredoc_eof_handler(t_heredoc *hdoc);
int				handle_heredoc_ast(t_ast *redir, t_shell *sh);
bool			process_heredoc_line(char *line, t_heredoc *hdoc,
					t_expand *exp, t_shell *sh);
int				handle_heredoc(t_ast_redirection *redir, t_shell *sh,
					t_expand *exp);
int				read_heredoc(t_heredoc *hdoc, t_shell *sh, t_expand *exp);

// ENV
t_env_list		*init_envp(char **envp);
int				is_valid_var_name(char *name);
char			*get_path_env(t_env_list *env);
void			sort_env_list(t_env_list *list);
t_env_list		*find_env_node(t_env_list *list, char *name);
void			update_env_node(t_env_list *list, char *var_name,
					char *var_value);
void			remove_env_node(t_env_list *list, char *var_name);
void			add_or_update_env(t_env_list *list, char *var_name,
					char *var_value);
void			add_env_node(t_env_list *list, char *var_name, char *var_value);

// BUILTINS
void			exec_pwd(void);
void			exec_echo(t_ast_command *cmd);
void			exec_env(t_env_list *env_list);
void			print_env_list(t_env_list *list);
void			exec_exit(t_shell *sh, t_ast_command *cmd, t_ast *ast);
void			exec_cd(t_ast_command *cmd, t_env_list *env_list);
void			exec_unset(t_env_list *env_list, t_ast_command *cmd);
void			exec_export(t_env_list *env_list, t_ast_command *cmd);

// CLEANING
void			free_ast(t_ast *node);
void			free_env_list(void *list);
void			handle_malloc_error(void);
void			free_env_array(char **envp);
void			handle_strdup_error(void *ptr);

void			free_list_token(t_token *token_list);

void			free_token_list(t_token *tokens);
int				report_syntax_error(t_shell *sh);
void			free_wildcards(t_wildcard *wildcards);
void			exit_shell(int exit_status, t_shell *sh);
void			*syntax_error(char *unexpected_token, t_shell *sh);
void			remove_list_node(t_token **node, t_token **head,
					void (*free_function)(void *), bool free_node);
void			error(char *context, char *description, int exit_status,
					t_shell *sh);
int				handle_parsing_error(t_shell *sh, t_token *token_lst);
void			ft_lstclear_env(t_env_list **lst, void (*del)(void *));

// TOKEN
int				is_blank(char c);
bool			is_word(t_token *token);
bool			is_redirect(t_token *token);
bool			is_special_operator(char c);
bool			is_operator(t_token *token);
int				ft_lstsize_token(t_token *token);
bool			is_open_parenthesis(t_token *token);
char			*get_token_string(t_token_type type);
bool			is_close_parenthesis(t_token *token);
void			ft_lstclear_token(t_token **lst, void (*del)(void *));
void			ft_lstdelone_token(t_token *lst, void (*del)(void *));
void			ft_lstadd_back_token(t_token **token_list, t_token *new_token);
void			add_front_token(t_token **token_list, t_ast *node, t_shell *sh);

// EXEC
char			*build_path(char *dir, char *command);
int				exec_pipeline(t_ast *node, t_shell *sh);
int				execute(t_ast *node, t_exit end, t_shell *sh);
int				exec_logical(t_ast_logical *logical, t_shell *sh);
char			**convert_env_list_to_array(t_env_list *env_list);
int				check_process_child_exit(int status, bool *new_line,
					t_shell *sh);
void			setup_for_next_command(int *prev_read_end, int p[2],
					t_shell *sh);
int				exec_subshell(t_ast_subshell *subshell, t_shell *sh);
int				append_output(t_ast_redirection *redir, t_shell *sh);
void			exec_extern_command(t_ast_command *cmd, t_shell *sh);
int				redirect_input(t_ast_redirection *redir, t_shell *sh);
int				redirect_output(t_ast_redirection *redir, t_shell *sh);
int				exec_redirection(t_ast_redirection *redir, t_shell *sh);
int				exec_command(t_ast_command *cmd, t_exit end, t_shell *sh,
					t_ast *ast);
int				wait_for_children(pid_t last_pid, int n_pipeline, t_shell *sh);

// PARSING
int				is_quoted(char *str);
int				count_arg(t_token *cur);
char			*remove_quotes(char *str);
t_ast			*create_ast_cmd(char **args);
t_ast			*parse_command(t_token **token);
void			init_ast_node(t_ast **node, t_ast_type type);
t_ast			*create_ast_subshell(t_ast *child, t_shell *sh);
int				parser(t_token *token, t_ast **ast, t_shell *sh);
t_ast			*parse_redirection(t_token **token, t_shell *sh);
t_ast			*parse_redirection_list(t_token **token, t_ast *command,
					t_shell *sh);
t_ast			*create_ast_redirection(t_token_type direction,
					t_token *filename, t_ast *command, t_shell *sh);
t_ast			*create_ast_logical(t_ast *left, t_token_type op,
					t_ast *right, t_shell *sh);
t_ast			*create_ast_pipeline(t_ast	*left, t_ast *right, t_shell *sh);
t_ast			*build_redir_cmd(t_ast *prefix, t_ast *suffix, t_ast *command);

// EXPANSION
char			*remove_wildcard(char *buf);
char			**expand_wildcard_dirs(void);
void			add_to_buffer(char *str, t_expand *exp);
bool			init_expansion(t_expand *exp, char *str,
					t_token **expanded_args, t_shell *sh);
t_ast			*node_expansion(t_ast *node, t_shell *sh);
void			command_expansion(t_ast *node, t_shell *sh);
t_token			*get_files_list(t_expand *exp, t_shell *sh);
char			**list_to_array(t_token **lst, t_shell *sh);
char			*extract_root_path(t_expand *exp, t_shell *sh);
void			*add_token_to_list(t_expand *exp, t_shell *sh);
void			expand_last_status(t_expand *exp, t_shell *sh);
void			*filename_expansion(t_expand *exp, t_shell *sh);
t_token			*pattern_filter(t_token *tokens, t_expand *exp);
void			redirection_expansion(t_ast *node, t_shell *sh);
bool			is_active_wildcard(int position, t_expand *exp);
void			expand_var(char *str, t_expand *exp, t_shell *sh);
bool			pattern_match(char *filename, char *pattern, int i);
t_token			*append_tokens_to_list(t_token *list, char **to_add);

bool			only_active_wildcard_left(char *str, t_expand *exp);
void			add_wildcard_pos(t_wildcard **wildcard_list, int pos,
					t_shell *sh);
void			add_expanded_value(char **value, char *expanded_value);
char			*get_valid_name(char *str, t_expand *exp, t_shell *sh);
char			*expand_env_var(char *str, t_expand *exp, t_shell *sh);
void			handle_redirection(char *input, int *pos, char **value);
void			list_of_file_to_token_list(t_token *tokens, t_expand *exp,
					t_shell *sh);
void			add_var_to_buffer(char *value, t_expand *exp, t_shell *sh);
char			*expand_heredoc_vars(char *line, t_shell *sh, t_expand *exp);
void			arg_expansion(char *str, t_token **expanded_args, t_shell *sh);
void			save_wildcards_pos(char *to_check, t_expand *exp, t_shell *sh);

#endif