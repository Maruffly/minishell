/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:19:25 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/24 18:56:53 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_and_backup_stdin(t_ast_redir *redir, t_shell *sh,
							int *original_stdin)
{
	int		input_fd;
	char	*file_name;

	file_name = remove_quotes(redir->file);
	input_fd = open(file_name, O_RDONLY);
	if (input_fd == -1)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		perror(redir->file);
		sh->redirection_error = true;
		return (-1);
	}
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
	{
		perror("dup");
		close(input_fd);
		return (-1);
	}
	return (input_fd);
}

int	redirect_stdin(int input_fd, int original_stdin)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(input_fd);
		close(original_stdin);
		return (-1);
	}
	close(input_fd);
	return (0);
}

int	setup_output_redirection(t_ast_redir *redir)
{
	int		output_fd;
	char	*file_name;

	file_name = remove_quotes(redir->file);
	output_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("file %s : create\n", file_name);
	if (output_fd == -1)
	{
		write(STDERR_FILENO, "Omar&Fred: ", 11);
		perror(redir->file);
		return (-1);
	}
	return (output_fd);
}

int	open_redirection_file(char *file, int is_trunc, t_shell *sh)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (is_trunc)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Omar&Fred: ", 11);
		perror(file);
		sh->redirection_error = true;
	}
	return (fd);
}

t_ast_redir	*find_last_redirection(t_ast_redir *redir)
{
	t_ast_redir	*cur;

	cur = redir;
	while (cur->command && cur->command->type == AST_REDIRECTION)
		cur = &cur->command->u_data.redirection;
	return (cur);
}
