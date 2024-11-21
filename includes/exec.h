/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:16:49 by jbmy              #+#    #+#             */
/*   Updated: 2024/11/21 17:36:39 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXEC_H
# define EXEC_H

# include <stdio.h>

# include "builtins.h"
# include "token.h"
# include "env.h"

// EXEC //
void	execute_pipeline(t_command *cmd, t_env_list *env);

// CHILD //
char	*get_path(char *cmd, char **envp);
void	redir_command(t_command *cmd);
void	close_unused_fds(t_command	*cmd);
void	setup_pipes(t_command *cmd);
int		update_prev_output_fd(t_command *cmd);

#endif
