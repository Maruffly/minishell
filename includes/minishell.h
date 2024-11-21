/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:12:58 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/21 18:28:38 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "../libft/libft.h"
# include "./builtins.h"
# include "./parsing.h"
# include "./token.h"
# include "./exec.h"
# include "./env.h"

// Macros
# define RESET	"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELL	"\e[33m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

// SIGNAL //
/* extern int	g_signal_received; */

// READ LINE //
void	read_line(t_command **cmd);

// INIT COMMAND STRUCT //


// EXIT //
void	free_cmd_list(t_command *head);
void 	free_token_list(t_token *tokens);
void	handle_exit_status(char *input, int *exit_code);

#endif
