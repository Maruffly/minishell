/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/20 13:43:40 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../includes/minishell.h"

void	skip_whitespace(char *line, int *pos)
{
	while (line[*pos] && is_blank(line[*pos]))
		(*pos)++;
}

/* t_token_type	get_token_type(char *token)
{
	if (is_NULL(token))
		return (0);
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token, "&&") == 0)
		return (AND);
	if (ft_strcmp(token, "||") == 0)
		return (OR);
	if (ft_strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIRECT_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (APPEND_OUT);
	if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	return (WORD);
} */
/*
char	*extract_word(char *line, int pos)
{
	int	start;

	start = pos;
	while (line[pos] && !is_blank(line[pos]) && !is_special_operator(line[pos]))
		pos++;
	return (ft_substr(line, start, pos - start));
} */

void ft_lstadd_back_token(t_token **token_list, t_token *new_token)
{
	t_token *last;

	if (!token_list || !new_token)
		return;

	if (*token_list == NULL)
	{
		*token_list = new_token;
		new_token->prev = NULL;
	}
	else
	{
		last = *token_list;
		while (last->next)
			last = last->next;
		last->next = new_token;
		new_token->prev = last;
	}
	new_token->next = NULL;
}

void	ft_lstdelone_token(t_token *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->value);
	free(lst);
}

void	ft_lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (*lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_token(*lst, del);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}


int	ft_lstsize_token(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}
