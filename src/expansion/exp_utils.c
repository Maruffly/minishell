/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:17 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/27 10:17:30 by jlaine           ###   ########.fr       */
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
		exp->context = NO_QUOTE;
		exp->empty_quotes = false;
		exp->tokens = expanded_args;
		exp->wildcards_position = NULL;
		exp->buf_size = ft_strlen(str) + 1;
		exp->buf = ft_calloc(ft_strlen(str) + 1, sizeof(char));
		if (!exp->buf)
			return (false);
		return (true);
	}
	else
	{
		ft_memset(exp, 0, sizeof(t_expand));
		exp->buf = ft_calloc(4096, sizeof(char));
		if (!exp->buf)
			return (false);
		exp->buf_size = 4096;
		exp->buf_i = 0;
		exp->i = 0;
		return (true);
	}
	return (false);
}

void	*add_token_to_list(t_expand *exp, t_shell *sh)
{
	char	*content;
	t_token	*new_token;

	if (!exp || !sh)
		return (NULL);
	if (exp->wildcards_position)
		filename_expansion(exp, sh);
	if (exp->buf_i > 0 || exp->empty_quotes)
	{
		if (exp->buf_i > 0)
		{
			content = ft_strdup(exp->buf);
			if (!content)
				return (NULL);
		}
		else
			content = ft_strdup("");
		if (!content)
			return (NULL);
		new_token = create_token(WORD, content, ft_strlen(content));
		if (!new_token)
		{
			free(content);
			return (NULL);
		}
		ft_lstadd_back_token(exp->tokens, new_token);
		exp->buf_i = 0;
		exp->empty_quotes = false;
	}
	return (NULL);
}

void add_var_to_buffer(char *value, t_expand *exp, t_shell *sh)
{
	int		i;
	char 	*new_buffer;
	size_t 	value_len;
	
	if (!value || !exp || !sh)
		return ;
	value_len = ft_strlen(value);
	if (sh->prompt_mode == MAIN_PROMPT)
	{
		exp->buf_size += value_len;
		new_buffer = ft_calloc(exp->buf_size, sizeof(char));
		if (!new_buffer)
		{
			free(exp->buf);
			exp->buf = NULL;
			return ;
		}
		if (exp->buf)
			ft_strlcpy(new_buffer, exp->buf, exp->buf_i + 1);
		ft_strlcat(new_buffer, value, exp->buf_size);
		free(exp->buf);
		exp->buf = new_buffer;
		exp->buf_i += value_len;
		save_wildcards_pos(value, exp, sh);
	}
	else
	{
		i = 0;
		while (value[i] && exp->buf_i < exp->buf_size - 1)
			exp->buf[exp->buf_i++] = value[i++];
		exp->buf[exp->buf_i] = '\0';
	}
}

char	*get_valid_name(char *str, t_expand *exp, t_shell *sh)
{
	int		j;
	char	*name;

	(void)sh;
	if (!str || !sh)
		return (NULL);
	j = exp->i + 1;
	if (!ft_isalpha(str[j]) && str[j] != '_')
		return (NULL);
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	name = ft_substr(str, exp->i + 1, j - (exp->i + 1));
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

// char	*word_splitting(t_expand *exp, char *value, t_shell *sh)
// {
// 	int		i;
// 	char	**split;

// 	if (!exp || !value || !sh)
// 		return (NULL);
// 	i = 0;
// 	split = ft_split(value, ' ');
// 	if (!split)
// 		return (NULL);
// 	while (split[i])
// 	{
// 		if (!add_token_to_list(exp, sh))
// 		{
// 			ft_free_split(split);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// 	return (value);
// }
