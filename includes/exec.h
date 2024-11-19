/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:16:49 by jbmy              #+#    #+#             */
/*   Updated: 2024/11/18 18:45:15 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXEC_H
# define EXEC_H

# include <stdio.h>

# include "builtins.h"
# include "token.h"

void	execute_commands(t_command *cmd, t_env_list *env);


#endif