/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/10 15:53:29 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_token_string(t_token_type type)
{
	if (type == PIPE)
		return ("|");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	else if (type == OPEN_PARENTHESIS)
		return ("(");
	else if (type == CLOSE_PARENTHESIS)
		return (")");
	else if (type == WORD)
		return ("word");
	else if (type == REDIRECT_IN)
		return ("<");
	else if (type == REDIRECT_OUT)
		return (">");
	else if (type == APPEND_OUT)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == WILDCARD)
		return ("*");
	else
		return ("[unknown token]");
}

int	is_quoted(char *str)
{
	size_t	len;
	char	quote;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	quote = str[0];
	if ((quote == '\'' || quote == '\"') && str[len - 1] == quote)
		return (1);
	return (0);
}

char	*remove_quotes(char *str)
{
	size_t	len;
	size_t	i;

	if (!str || !*str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (NULL);
	if (str[0] == '\'' || str[0] == '\"')
	{
		i = 0;
		while (i < len - 1)
		{
			str[i] = str[i + 1];
			i++;
		}
		str[len - 2] = '\0';
	}
	return (str);
}

int	count_arg(t_token *cur)
{
	int	i;

	i = 0;
	while (cur && is_word(cur))
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

/* t_ast	*parse_command(t_token **token)
{
	t_token	*cur;
	int		arg_count;
	char	**args;
	int		i;

	cur = *token;
	arg_count = count_arg(cur);
	if (!arg_count)
		return (NULL);
	args = ft_calloc((arg_count + 1), sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	cur = *token;
	while (cur && is_word(cur))
	{
		args[i] = ft_strdup(cur->value);
		if (!args)
			return (ft_free_split(args), NULL);
		i++;
		cur = cur->next;
	}
	args[arg_count] = NULL;
	return (create_ast_cmd(args));
} */

t_ast *parse_command(t_token **token)
{
	t_token *cur;
	int arg_count;
	t_ast *node;
	int i;

	cur = *token;
	arg_count = count_arg(cur);
	if (!arg_count)
		return (NULL);

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = AST_COMMAND;
	node->u_data.command.args = ft_calloc((arg_count + 1), sizeof(char *));
	if (!node->u_data.command.args)
	{
		free(node);
		return (NULL);
	}
	i = 0;
	cur = *token;
	while (cur && is_word(cur))
	{
		node->u_data.command.args[i] = ft_strdup(cur->value);
		if (!node->u_data.command.args[i])
		{
			ft_free_split(node->u_data.command.args);
			free(node);
			return (NULL);
		}
		i++;
		cur = cur->next;
	}
	node->u_data.command.args[arg_count] = NULL;
	return (node);
}
