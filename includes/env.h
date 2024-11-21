/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:35:10 by jbmy              #+#    #+#             */
/*   Updated: 2024/11/21 10:50:07 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ENV_H
# define ENV_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<string.h>
# include	<errno.h>

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

// ENVIRONEMENT //

t_env_list	*init_env_list(void);
void		free_env_list(t_env_list *list);
void		print_env_list(t_env_list *list);
void		update_env_node(t_env_list *list, char *var_name, char *var_value);
void		add_env_node(t_env_list *list, char *var_name, char *var_value);
void		remove_env_node(t_env_list *list, char *var_name);
t_env_node	*find_env_node(t_env_list *list, char *name);
void		update_pwd_env(t_env_list *env_list);
int			is_valid_var_name(char *name);
t_env_list	*envp_to_list(char **envp);
char		**list_to_envp(t_env_list *env);
void		check_env_path(char **envp);




#endif
