/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:03:03 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/09 14:49:14 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

bool	handle_redirections(t_token *cur, t_command *cmd)
{
	if (!cur || !cmd)
		return (false);
	if (cur->type == REDIRECT_IN)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(cur->next->value);
		cmd->input_fd = open(cmd->infile, O_RDONLY);

		if (cmd->input_fd < 0)
		{
			perror("Error opening input file");
			cmd->error = true;
			return (false);
		}
	}
	else if (cur->type == REDIRECT_OUT)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(cur->next->value);
		cmd->output_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->output_fd < 0)
		{
			perror("Error opening output file");
			cmd->error = true;
			return (false);
		}
	}
	else if (cur->type == APPEND_OUT)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(cur->next->value);
		cmd->output_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->output_fd < 0)
		{
			perror("Error opening output file");
			cmd->error = true;
			return (false);
		}
		cmd->append_mode = true;
	}
	else if (cur->type == HEREDOC) // '<<'
	{
		if (cmd->heredoc_limiter)
			free(cmd->heredoc_limiter);
		cmd->heredoc_limiter = ft_strdup(cur->next->value);
		cmd->heredoc_mode = true;
	}
	return (true);
}

void handle_pipeline(t_command **head, t_command **cmd, t_token *start, t_token *stop)
{
	if (!*cmd)
		return;
	(*cmd)->args = token_to_args(start, stop);
	if (!(*cmd)->args)
	{
		(*cmd)->args = malloc(sizeof(char *) * 2);
		if (!(*cmd)->args)
		{
			free(*cmd);
			*cmd = NULL;
			return ;
		}
		(*cmd)->args[0] = ft_strdup((*cmd)->command);
		(*cmd)->args[1] = NULL;
	}
	add_command(head, *cmd);
	*cmd = NULL;
}


t_command	*process_pipeline(t_token *cur, t_command *cur_cmd, t_command **head, t_token **start)
{
	t_token	*stop;

	if ((cur->type == PIPE || !cur->next) && cur_cmd)
	{
		if (cur->type == PIPE)
			stop = cur;
		else
			stop = cur->next;
		cur_cmd->args = token_to_args(*start, stop);
		add_command(head, cur_cmd);
		cur_cmd = NULL;
		if (cur->type == PIPE)
			stop = cur->next;
		else
			stop = cur;
	}
	return (cur_cmd);
}


