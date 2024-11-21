/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:10:50 by jbmy              #+#    #+#             */
/*   Updated: 2024/11/21 16:51:02 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_token	identify_token_type(char *token);

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_fd = 0;
	cmd->output_fd = 1;
	cmd->next = NULL;
	return (cmd);
}

char	**ft_add_to_array(char **array, char *new_element)
{
	int		i;
	char	**new_array;

	i = 0;
	while (array && array[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = ft_strdup(new_element);
	if (!new_array[i])
		return (free(new_array), NULL);
	new_array[i + 1] = NULL;
	free(array);
	return (new_array);
}

void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*cur;

	if (!head || !new_cmd)
		return ;
	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	cur = *head;
	while (cur->next)
			cur = cur->next;
	cur->next = new_cmd;
}

t_command	*parse_input(char *input)
{
	char		**tokens;
	int			i;
	t_command	*head;
	t_command	*cmd;

	if (!*input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	head = NULL;
	i = 0;
	while (tokens[i])
	{
		cmd = init_command();
		if (!cmd)
			return (free_cmd_list(head), ft_free_split(tokens), NULL);
		cmd->type = identify_token_type(tokens[i]);
		if (cmd->type == CMD || cmd->type == ARG)
		{
			cmd->args = ft_add_to_array(cmd->args, tokens[i]);
			if (!cmd->args)
			{
					free_cmd_list(cmd);
					ft_free_split(tokens);
					return (NULL);
			}
			i++;
		}
		else if (cmd->type == PIPE || cmd->type == REDIRECT_OUT
			|| cmd->type == REDIRECT_IN || cmd->type == APPEND_OUT
			|| cmd->type == HEREDOC)
		{
			i++;
			if (tokens[i])
			{
				cmd->args = ft_add_to_array(cmd->args, tokens[i]);
				if (!cmd->args)
				{
					free_cmd_list(cmd);
					ft_free_split(tokens);
					return (NULL);
				}
				i++;
			}
		}
		else
			i++;
		add_command(&head, cmd);
	}
	ft_free_split(tokens);
	return (head);
}

void	free_cmd_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			ft_free_split(cmd->args);
		free(cmd);
		cmd = tmp;
	}
}

