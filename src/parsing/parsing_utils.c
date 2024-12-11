/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/11 14:06:23 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*get_last_child_redir(t_ast *node)
{
	while (node && node->type == AST_REDIRECTION
	&& node->u_data.redirection.child
	&& node->u_data.redirection.child->type == AST_REDIRECTION)
	node = node->u_data.redirection.child;
	return (node);
}

t_ast	*build_redir_cmd(t_ast *prefix, t_ast *suffix, t_ast *command)
{
	t_ast	*last_child;

	if (prefix && suffix)
	{
		last_child = get_last_child_redir(prefix);
		last_child->u_data.redirection.child = suffix;
		last_child = get_last_child_redir(suffix);
		last_child->u_data.redirection.child = command;
		return (prefix);
	}
	else if (!prefix && suffix)
	{
		last_child = get_last_child_redir(suffix);
		last_child->u_data.redirection.child = command;
		return (suffix);
	}
	else if (prefix && !suffix)
	{
		last_child = get_last_child_redir(prefix);
		last_child->u_data.redirection.child = command;
		return (prefix);
	}
	else
		return (command);
}

t_ast	*get_last_child_redir(t_ast *node)
{
	while (node && node->type == AST_REDIRECTION
	&& node->u_data.redirection.child
	&& node->u_data.redirection.child->type == AST_REDIRECTION)
	node = node->u_data.redirection.child;
	return (node);
}

bool	is_syntax_ok(t_token *new_token, t_token *head)
{
	if (!head && new_token->type == PIPE)
	{
		printf("Syntax error : unexpected token '|'\n ");
		return (false);
	}
	if (new_token->type == PIPE && (!head || !head->next))
	{
		printf("Syntax error : incomplete pipe sequence\n");
		return (false);
	}
	if ((new_token->type == REDIRECT_IN || new_token->type == REDIRECT_OUT
		|| new_token->type == APPEND_OUT || new_token->type == HEREDOC)
		&& (!head || !head->next))
		{
			ft_putstr_fd("Syntax error: invalid redirection missing argument\n", STDERR_FILENO);
			return (false);
}
	return (true);
}

bool	is_blank_line(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!is_blank(*line))
			return (false);
		line++;
	}
	return (true);
}

/* t_command	*handle_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	return (NULL);
} */

bool	is_empty_line(char *input)
{
	int	i;

	if (!input) // Si la ligne est NULL (sécurité supplémentaire)
		return (true);
	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (input[i] == '\0'); // Retourne true si la ligne est vide après trim
}

void	add_arg_tab(char ***array, char *new_arg)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	while ((*array) && (*array)[i])
		i++;
	new_array = ft_calloc(i + 2, sizeof(char *));
	if (!new_array)
		return ;
	j = 0;
	while (j < i)
	{
		new_array[j] = (*array)[j];
		j++;
	}
	new_array[i] = new_arg;
	new_array[i + 1] = NULL;
	*array = new_array;
}
