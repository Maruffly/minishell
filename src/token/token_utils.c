/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/11 14:54:28 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../includes/minishell.h"

void	skip_whitespace(char *line, int *pos)
{
	while (line[*pos] && is_blank(line[*pos]))
		(*pos)++;
}

t_token_type	get_token_type(char *token)
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
}

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
	else
		return ("[unknown token]");
}

char	*extract_word(char *line, int pos)
{
	int	start;

	start = pos;
	while (line[pos] && !is_blank(line[pos]) && !is_special_operator(line[pos]))
		pos++;
	return (ft_substr(line, start, pos - start));
}

void lst_add_back_token(t_token **token_list, t_token *new_token)
{
	t_token *last;

	if (!token_list || !new_token)
		return;

	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		last = *token_list;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}
void	ft_lstdelone(t_env_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->var_value);
	free(lst);
}

void	ft_lstclear(t_env_list **lst, void (*del)(void *))
{
	t_env_list	*tmp;

	if (*lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}
