/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:17 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:19:26 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_exp(t_exp *exp, char *str, t_list **expanded_args,
	t_shell *sh)
{
exp->i = 0;
exp->buf_size = ft_strlen(str) + 1;
exp->buf = calloc_s(ft_strlen(str) + 1, sizeof(char), PROMPT, sh);
exp->buf_i = 0;
exp->context = NO_QUOTE;
exp->tokens = expanded_args;
exp->empty_quotes = false;
exp->wildcards_position = NULL;
}

void	*add_token_to_list(t_exp *exp, t_shell *sh)
{
char	*content;

if (exp->wildcards_position)
	filename_expansion(exp, sh);
if (exp->buf_i != 0)
{
	exp->buf[exp->buf_i] = '\0';
	content = strdup_s(exp->buf, PROMPT, sh);
	lst_add_back_s(content, exp->tokens, PROMPT, sh);
	exp->buf_i = 0;
}
else if (exp->empty_quotes)
{
	content = strdup_s("", PROMPT, sh);
	lst_add_back_s(content, exp->tokens, PROMPT, sh);
	exp->empty_quotes = false;
}
return (NULL);
}

void	add_variable_to_buffer(char *value, t_exp *exp, t_shell *sh)
{
char	*buf_replace;

exp->buf_size += ft_strlen(value);
saved_wildcards_position(value, exp, sh);
buf_replace = calloc_s(exp->buf_size, sizeof(char), PROMPT, sh);
ft_strlcpy(buf_replace, exp->buf, exp->buf_i + 1);
ft_strlcat(buf_replace, value, exp->buf_i + ft_strlen(value) + 1);
exp->buf = buf_replace;
exp->buf_i += ft_strlen(value);
}

char	**convert_list_to_array(t_list **lst, t_shell *sh)
{
t_list	*tmp;
char	**args;
int		i;

i = 0;
tmp = *lst;
args = (char **)calloc_s(ft_lstsize(tmp) + 1, sizeof(char *), PROMPT,
		sh);
while (tmp != NULL)
{
	args[i++] = (char *)tmp->content;
	tmp = tmp->next;
}
args[i] = NULL;
return (args);
}

char	*word_splitting(t_exp *exp, char *value, t_shell *sh)
{
	char	**split;

	if (strlen(value) == 0)
		return (value);
	split = split_s(value, ' ', PROMPT, sh);
	if (!*split)
		return (add_token_to_list(exp, sh));
	if (ft_strcmp(value, split[0]) == 0)
		return (value);
	if (*split && value[0] != ' ')
	{
		add_variable_to_buffer(*split++, exp, sh);
		if (!*split)
			return (add_token_to_list(exp, sh));
	}
	else
		add_token_to_list(exp, sh);
	while (*split)
	{
		add_token_to_list(exp, sh);
		if (!*(split + 1) && value[ft_strlen(value) - 1] != ' ')
			return (*split);
		lst_add_back_s(*split++, exp->tokens, PROMPT, sh);
	}
	return (NULL);
}
