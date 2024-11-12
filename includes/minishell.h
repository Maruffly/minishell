/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:12:58 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/12 18:10:22 by jlaine           ###   ########.fr       */
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
/* # include "./parsing.h"
# include "./builtins.h" */

// Macros
# define RESET	"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELL	"\e[33m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

typedef struct s_env_node
{
	char				*var_name;
	char				*var_value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env_list
{
	struct s_env_node	*head;
}	t_env_list;

void	read_line(void);

// ENVIRONEMENT //

t_env_list	*init_env_list(void);
void		free_env_list(t_env_list *list);
void		print_env_list(t_env_list *list);
void		update_env_node(t_env_list *list, char *var_name, char *var_value);
void		add_env_node(t_env_list *list, char *var_name, char *var_value);
void		remove_env_node(t_env_list *list, char *var_name);
t_env_node	*find_env_node(t_env_list *list, char *name);
void		update_pwd_env(t_env_list *env_list);

// EXIT //
void	handle_exit_status(const char *input, int *exit_code);


#endif
