/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:48 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/12 17:16:46 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTINS_H
# define BUILTINS_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<string.h>
# include	<errno.h>

# include "minishell.h"

# include "./minishell.h"
# include "../libft/libft.h"
# include "./parsing.h"

// BUILT-INS EXEC //
void	exec_cd(t_command *cmd, t_env_list *env_list);
void	exec_echo(t_command *cmd);
void	exec_env(t_env_list *env_list);
void	exec_exit(t_env_list *env_list, t_command *cmd);
void	exec_export(t_env_list *env_list, t_command *cmd);
void	exec_pwd(t_env_list *env_list);
void	exec_unset(t_env_list *env_list, t_command *cmd);

#endif
