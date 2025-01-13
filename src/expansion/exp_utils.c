/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:17 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/10 16:59:26 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	init_expansion(t_expand *exp, char *str, t_token **expanded_args,
						t_shell *sh)
{
	if (sh->prompt_mode == MAIN_PROMPT)
	{
		exp->i = 0;
		exp->buf_i = 0;
		exp->context = NO_QUOTE;
		exp->empty_quotes = false;
		exp->tokens = expanded_args;
		exp->wildcards_position = NULL;
		exp->buf_size = ft_strlen(str) + 1; // SEGFAULT
		exp->buf = ft_calloc(ft_strlen(str) + 1, sizeof(char));
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

void	no_quote(char *str, t_expand *exp, t_shell *sh)
{
	if (str[exp->i] == '$')
		expand_var(str, exp, sh);
	else if (str[exp->i] == ' ')
		add_token_to_list(exp, sh);
	else if (str[exp->i] == '\"')
		exp->context = IN_DOUBLE_QUOTE;
	else if (str[exp->i] == '\'')
		exp->context = IN_SINGLE_QUOTE;
	else if (str[exp->i] == '\\')
		exp->buf[exp->buf_i++] = str[++exp->i];
	else
	{
		if (str[exp->i] == '*')
			save_wildcards_pos("*", exp, sh);
		exp->buf[exp->buf_i++] = str[exp->i];
	}
}

void	single_quote(char *str, t_expand *exp)
{
	if (str[exp->i] == '\'')
	{
		if (exp->buf_i == 0)
			exp->empty_quotes = true;
		exp->context = NO_QUOTE;
	}
	else
		exp->buf[exp->buf_i++] = str[exp->i];
}

void	double_quote(char *str, t_expand *exp, t_shell *sh)
{
	if (str[exp->i] == '$')
		expand_var(str, exp, sh);
	else if (str[exp->i] == '\"')
	{
		if (exp->buf_i == 0)
			exp->empty_quotes = true;
		exp->context = NO_QUOTE;
	}
	else if (str[exp->i] == '\\' &&
			(str[exp->i + 1] == '\"' || str[exp->i + 1] == '\\'))
	{
		exp->i++;
		exp->buf[exp->buf_i++] = str[exp->i];
	}
	else
		exp->buf[exp->buf_i++] = str[exp->i];
}

void	*add_token_to_list(t_expand *exp, t_shell *sh)
{
	char	*content;
	t_token	*new_token;

	if (exp->wildcards_position)
		filename_expansion(exp, sh);
	if (exp->buf_i > 0 || exp->empty_quotes)
	{
		if (exp->buf_i > 0)
			content = ft_strdup(exp->buf);
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

void	add_var_to_buffer(char *value, t_expand *exp, t_shell *sh)
{
	char	*new_buffer;

	if (sh->prompt_mode == MAIN_PROMPT)
	{
		exp->buf_size += ft_strlen(value);
		save_wildcards_pos(value, exp, sh);
		new_buffer = ft_calloc(exp->buf_size, sizeof(char));
		ft_strlcpy(new_buffer, exp->buf, exp->buf_i + 1);
		ft_strlcpy(new_buffer, value, exp->buf_i + ft_strlen(value) + 1);
		exp->buf = new_buffer;
		exp->buf_i += ft_strlen(value);
	}
	else
	{
		int	i;

		i = 0;
		while (value && value[i])
		{
			if (exp->buf_i < exp->buf_size - 1)
				exp->buf[exp->buf_i++] = value[i];
			else
				break;
			i++;
		}
		exp->buf[exp->buf_i] = '\0';
	}
}

char	*get_valid_name(char *str, t_expand *exp, t_shell *sh)
{
	int		j;
	char	*name;

	(void)sh;
	j = exp->i + 1;
	if (!ft_isalpha(str[j]) && str[j] != '_')
		return (NULL);
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	name = ft_substr(str, exp->i + 1, j = exp->i - 1);
	return (name);
}

char	**list_to_array(t_token **lst, t_shell *sh)
{
	int		i;
	char	**args;
	t_token	*current;

	i = 0;
	(void)sh;
	current = *lst;
	args = (char **)ft_calloc(ft_lstsize_token(current) + 1, sizeof(char *));
	while (current)
	{
		args[i++] = (char *)current->value;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

char	*word_splitting(t_expand *exp, char *value, t_shell *sh) // TO REWORK
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(value, ' ');
	if (!split)
		return (NULL);
	while (split[i])
	{
		add_token_to_list(exp, sh);
		i++;
	}
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (value);
}
