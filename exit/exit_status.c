/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:58:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/12 18:10:08 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"
# include	"../../includes/parsing.h"
# include	"../../includes/token.h"

static void	print_exit_code(int	exit_code)
{
	printf("%d\n", exit_code);
}

static void	set_exit_code(int *exit_code, int code)
{
	*exit_code = code;
	print_exit_code(*exit_code);
}

void	handle_exit_status(const char *input, int *exit_code)
{
	if (ft_strcmp(input, "$?") == 0)
		print_exit_code(*exit_code);
	else if (ft_strcmp(input, "Ctrl+C") == 0)
		set_exit_code(exit_code, 130);
	else if (ft_strcmp(input, "Ctrl+\\") == 0)
		set_exit_code(exit_code, 131);
	else if (ft_strcmp(input, "command_not_found") == 0)
		set_exit_code(exit_code, 127);
	else if (ft_strcmp(input, "permission_denied") == 0)
		set_exit_code(exit_code, 126);
	else
		set_exit_code(exit_code, 1);
}