/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:17 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/10 19:16:54 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	init_expansion(t_expand *exp, char *str, t_token **expanded_args,
						t_shell *sh)
{
	if (!exp || !sh)
		return (false);
	if (sh->prompt_mode == MAIN_PROMPT)
	{
		exp->i = 0;
		exp->buf_i = 0;
		exp->expandable = true;
		exp->has_match = false;
		exp->context = NO_QUOTE;
		exp->empty_quotes = false;
		exp->tokens = expanded_args;
		exp->wildcards_position = NULL;
		exp->buf_size = ft_strlen(str) + 1;
		exp->buf = ft_calloc(exp->buf_size, sizeof(char));
		return (exp->buf != NULL);
	}
	ft_memset(exp, 0, sizeof(t_expand));
	exp->buf = ft_calloc(4096, sizeof(char));
	exp->buf_size = 4096;
	return (exp->buf != NULL);
}

void	add_var_to_buffer(char *str, t_expand *exp, t_shell *sh)
{
	char	*new_buffer;
	size_t	str_len;

	if (!str || !exp || !sh)
		return ;
	str_len = ft_strlen(str);
	exp->buf_size += str_len;
	new_buffer = ft_calloc(exp->buf_size, sizeof(char));
	if (!new_buffer)
	{
		free(exp->buf);
		exp->buf = NULL;
		return ;
	}
	if (exp->buf)
		ft_strlcpy(new_buffer, exp->buf, exp->buf_i + 1);
	ft_strlcat(new_buffer, str, exp->buf_size);
	free(exp->buf);
	exp->buf = new_buffer;
	exp->buf_i += str_len;
	save_wildcards_pos(str, exp, sh);
}

void	add_to_buffer(char *str, t_expand *exp)
{
	int	len;

	len = ft_strlen(str);
	if (exp->buf_i + len >= exp->buf_size)
	{
		exp->buf_size = exp->buf_i + len + 1;
		exp->buf = ft_realloc(exp->buf, exp->buf_size);
		if (!exp->buf)
			return ;
	}
	ft_strlcpy(exp->buf + exp->buf_i, str, len + 1);
	exp->buf_i += len;
}

char	*get_valid_name(char *str, t_expand *exp, t_shell *sh)
{
	int		j;
	char	*name;
	int		start;

	(void)sh;
	if (!str || !sh)
		return (NULL);
	if (exp->context == IN_SINGLE_QUOTE)
		return (NULL);
	j = exp->i + 1;
	if (sh->prompt_mode == HEREDOC_PROMPT)
	{
		while (str[j] == '\'' || str[j] == '\"')
			j++;
	}
	if (!ft_isalpha(str[j]) && str[j] != '_')
		return (NULL);
	if (sh->prompt_mode == HEREDOC_PROMPT)
		start = j - 1;
	if (sh->prompt_mode == MAIN_PROMPT)
		start = j;
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	name = ft_substr(str, start, j - start);
	return (name);
}

char	**list_to_array(t_token **lst, t_shell *sh)
{
	int		i;
	char	**args;
	t_token	*current;

	if (!lst || !sh)
		return (NULL);
	i = 0;
	(void)sh;
	current = *lst;
	args = (char **)ft_calloc(ft_lstsize_token(current) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (current)
	{
		args[i++] = (char *)current->value;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}
