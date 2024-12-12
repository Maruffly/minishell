/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:58:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/12 13:33:57 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../includes/minishell.h"

static void	print_exit_code(int	exit_code)
{
	printf("%d\n", exit_code);
}

static void	set_exit_code(int *exit_code, int code)
{
	*exit_code = code;
	print_exit_code(*exit_code);
}

void	handle_exit_status(char *input, int *exit_code)
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

void	exit_shell(int exit_status, t_shell *sh)
{
	if (sh)
	{
		if (sh->is_parent && isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_lstclear(&sh->env, free_env_list);
	}
	rl_clear_history();
	exit(exit_status);
}

/* int	report_error(char *context, char *element, char *description, t_shell *sh)
{
	write_s("minishell: ", STDERR_FILENO, sh);
	write_s(context, STDERR_FILENO, sh);
	if (element)
		write_s(element, STDERR_FILENO, sh);
	write_s(description, STDERR_FILENO, sh);
	write_s("\n", STDERR_FILENO, sh);
	return (EXIT_FAILURE);
} */

void	*syntax_error(char *unexpected_token, t_shell *sh)
{
	if (!sh->parsing_error)
		sh->parsing_error = unexpected_token;
	return (NULL);
}
int	report_syntax_error(t_shell *sh)
{
	/* report_error("syntax error near unexpected token `",
		sh->parsing_error, "'", sh); */
	sh->parsing_error = NULL;
	return (2);
}
