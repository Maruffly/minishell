/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:35:41 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:24:07 by jlaine           ###   ########.fr       */
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


// EXEC
char			**build_paths_array(t_shell *sh);
t_builtin_func	get_builtin_function(char *cmd_name);
char			*get_bin_path(char *bin, t_shell *sh);
int				exec_pipeline(t_ast *node, t_shell *sh);
int				execute_heredocs(t_ast *node, t_shell *sh);
int				exec_redir(t_ast_redirection *redir, t_shell *sh);
char			*join_path(char *path_to, char *file, t_shell *sh);
int				exec_subshell(t_ast_subshell *subshell, t_shell *sh);
int				fork_command(t_ast_command *cmd, t_execute_end end,
					t_shell *sh);
int				execute_logical(t_ast_logical *logical, t_shell *sh);
void			setup_for_next_command(int *prev_read_end, int p[2],
					t_shell *sh);
int				exec_cmd(t_ast_command *cmd, t_execute_end end, t_shell *sh);
int				wait_for_children(pid_t last_pid, int n_pipeline, t_shell *sh);

#endif