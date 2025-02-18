/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:26:54 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/18 13:00:51 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_ast	*parse_command(t_token **token)
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
}

int	check_redirection_access(t_token *cur, t_shell *sh)
{
	int	fd;

	if (cur->type == REDIRECT_IN)
	{
		if (access(cur->next->value, F_OK) == -1)
			return (handle_redirection_error(cur->next->value, sh), -1);
	}
	else if (cur->type == REDIRECT_OUT || cur->type == APPEND_OUT)
	{
		fd = open(cur->next->value, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (handle_redirection_error(cur->next->value, sh), -1);
		close(fd);
		if (cur->type == REDIRECT_OUT)
			fd = open(cur->next->value, O_WRONLY | O_TRUNC);
		else
			fd = open(cur->next->value, O_WRONLY | O_APPEND);
		if (fd == -1)
			return (handle_redirection_error(cur->next->value, sh), -1);
		close(fd);
	}
	return (0);
}
