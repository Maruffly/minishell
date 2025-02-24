/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/24 17:42:20 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	redirect_input(t_ast_redirection *redir, t_shell *sh)
{
	int	status;
	int	original_stdin;
	int	input_fd;

	input_fd = open_and_backup_stdin(redir, sh, &original_stdin);
	if (input_fd == -1)
		return (EXIT_FAILURE);
	if (redirect_stdin(input_fd, original_stdin) == -1)
		return (EXIT_FAILURE);
	status = EXIT_SUCCESS;
	if (redir->command)
		status = execute(redir->command, KEEP_RUNNING, sh);
	if (dup2(original_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(original_stdin);
		return (EXIT_FAILURE);
	}
	close(original_stdin);
	return (status);
}

int	redirect_output(t_ast_redirection *redir, t_shell *sh) // testtt
{
	int		status;
	int		output_fd;
	int		original_stdout;
	t_ast	*cmd_node;
	t_ast_redirection *cur;
	t_ast_redirection *last_redir;

	// ✅ 1. Parcourir toutes les redirections pour créer les fichiers
	cur = redir;
	last_redir = redir;
	while (cur)
	{
		// Créer tous les fichiers `>` et `>>`
		output_fd = open(cur->file, O_WRONLY | O_CREAT | ((cur->direction == REDIRECT_OUT) ? O_TRUNC : O_APPEND), 0644);
		printf("file %s : create\n", cur->file);
		if (output_fd == -1)
		{
			write(STDERR_FILENO, "Omar&Fred: ", 11);
			perror(cur->file);
			sh->redirection_error = true;
			return (EXIT_FAILURE);
		}
		close(output_fd); // On ferme le fichier immédiatement après l'avoir créé

		// ✅ Garder une référence uniquement vers la dernière redirection
		last_redir = cur;
		cur = (cur->command && cur->command->type == AST_REDIRECTION) ? &cur->command->u_data.redirection : NULL;
	}

	// ✅ 2. Appliquer uniquement la dernière redirection à `stdout`
	output_fd = open(last_redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
	{
		write(STDERR_FILENO, "Omar&Fred: ", 11);
		perror(last_redir->file);
		sh->redirection_error = true;
		return (EXIT_FAILURE);
	}

	original_stdout = dup(STDOUT_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);

	// ✅ 3. Exécuter la commande après avoir appliqué les redirections
	cmd_node = last_redir->command;
	while (cmd_node && cmd_node->type == AST_REDIRECTION)
		cmd_node = cmd_node->u_data.redirection.command;

	status = EXIT_SUCCESS;
	if (cmd_node)
		status = execute(cmd_node, KEEP_RUNNING, sh);

	// ✅ 4. Restaurer la sortie standard si nécessaire
	if (sh->is_parent && original_stdout != -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	return (status);
}


int	append_output(t_ast_redirection *redir, t_shell *sh)
{
	int	status;
	int	output_fd;
	int	original_stdout;

	output_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (output_fd == -1)
	{
		write(STDERR_FILENO, "Omar&Fred: ", 11);
		perror(redir->file);
		return (EXIT_FAILURE);
	}
	if (sh->is_parent)
		original_stdout = dup(STDOUT_FILENO);
	else
		original_stdout = -1;
	original_stdout = dup(STDOUT_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	status = execute(redir->command, KEEP_RUNNING, sh);
	if (sh->is_parent && original_stdout != -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	return (status);
}

int	redirect_heredoc(t_ast_redirection *redir, t_shell *sh)
{
	int		status;
	int		original_stdin;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
	{
		perror("dup");
		return (EXIT_FAILURE);
	}
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(original_stdin);
		return (EXIT_FAILURE);
	}
	status = execute(redir->command, KEEP_RUNNING, sh);
	if (dup2(original_stdin, STDIN_FILENO))
	{
		perror("dup2");
		close(original_stdin);
		return (EXIT_FAILURE);
	}
	close (original_stdin);
	return (status);
}

int	exec_redirection(t_ast_redirection *redir, t_shell *sh)
{
	int	status;

	status = EXIT_FAILURE;
	if (redir->direction == REDIRECT_IN)
		status = redirect_input(redir, sh);
	else if (redir->direction == HEREDOC)
		status = redirect_heredoc(redir, sh);
	else if (redir->direction == REDIRECT_OUT)
		status = redirect_output(redir, sh);
	else if (redir->direction == APPEND_OUT)
		status = append_output(redir, sh);
	if (status == EXIT_FAILURE)
		sh->last_status = EXIT_FAILURE;
	return (status);
}
