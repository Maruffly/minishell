/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:40:18 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:24:00 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_active_wildcard(int i, t_exp *exp)
{
	t_list	*tmp;

	tmp = exp->wildcards_position;
	while (tmp)
	{
		if (*((int *)(tmp->content)) == i)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	list_of_file_to_token_list(t_list *lst, t_exp *exp, t_shell *sh)
{
	while (lst)
	{
		lst_add_back_s(lst->content, exp->tokens, PROMPT, sh);
		lst = lst->next;
	}
}

void	saved_wildcards_position(char *to_check, t_exp *exp, t_shell *sh)
{
	int	i;
	int	*position;

	i = 0;
	if (exp->context != NO_QUOTE)
		return ;
	while (to_check[i])
	{
		if (to_check[i] == '*')
		{
			position = calloc_s(1, sizeof(int), PROMPT, sh);
			*((int *)position) = exp->buf_i + i;
			lst_add_back_s(position, &exp->wildcards_position, PROMPT, sh);
		}
		i++;
	}
}

bool	only_active_wildcard_left(const char *str, t_exp *exp)
{
	if (!str || !*str)
		return (false);
	while (*str)
	{
		if (*str != '*' || !is_active_wildcard(exp->buf_i, exp))
			return (false);
		str++;
	}
	return (true);
}

char	*extract_root_path(t_exp *exp, t_shell *sh)
{
	char	*path;
	int		i;

	i = exp->buf_i - 1;
	while (i >= 0 && exp->buf[i] != '/')
		i--;
	if (i == -1)
		return (strdup_s(".", PROMPT, sh));
	path = calloc_s(i + 2, sizeof(char), PROMPT, sh);
	ft_strlcpy(path, exp->buf, i + 2);
	return (path);
}
