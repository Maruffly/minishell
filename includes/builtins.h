/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:48 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/13 17:38:28 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTINS_H
# define BUILTINS_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<string.h>
# include	<errno.h>

# include "../libft/libft.h"
# include "./parsing.h"
# include "./env.h"

// BUILT-INS EXEC //
void	exec_cd(t_command *cmd, t_env_list *env_list);
void	exec_echo(t_command *cmd);
void	exec_env(t_env_list *env_list);
void	exec_exit(t_env_list *env_list, t_command *cmd);
void	exec_export(t_env_list *env_list, t_command *cmd);
void	exec_pwd(t_env_list *env_list);
void	exec_unset(t_env_list *env_list, t_command *cmd);

#endif
