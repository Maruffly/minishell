/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:40:18 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 09:47:54 by jlaine           ###   ########.fr       */
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
		safe_lst_addback(lst->content, exp->tokens, PROMPT, sh);
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
			position = safe_calloc(1, sizeof(int), PROMPT, sh);
			*((int *)position) = exp->buf_i + i;
			safe_lst_addback(position, &exp->wildcards_position, PROMPT, sh);
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
		return (safe_strdup(".", PROMPT, sh));
	path = safe_calloc(i + 2, sizeof(char), PROMPT, sh);
	ft_strlcpy(path, exp->buf, i + 2);
	return (path);
}
