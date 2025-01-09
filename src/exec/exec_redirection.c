/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:44:28 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/09 17:49:32 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	exec_redirection(t_ast_redirection *redir, t_shell *sh)
{
	int	status;

	status = EXIT_FAILURE;
	if (redir->direction == REDIRECT_IN || redir->direction == HEREDOC)
		status = redirect_input(redir, sh); // TO DO
	else if (redir->direction == REDIRECT_OUT)
		status = redirect_output(redir, sh); // TO DO
	else if (redir->direction == APPEND_OUT)
		status = append_output(redir, sh); // TO DO
	return (status);
}

