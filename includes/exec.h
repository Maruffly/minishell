/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:16:49 by jbmy              #+#    #+#             */
/*   Updated: 2024/11/19 17:05:39 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXEC_H
# define EXEC_H

# include <stdio.h>

# include "builtins.h"
# include "token.h"
# include "env.h"

void	execute_commands(t_command *cmd, t_env_list *env);


#endif
