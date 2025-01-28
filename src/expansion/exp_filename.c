/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:17:13 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/28 14:29:55 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_file_token(t_token *cur, t_token **files, t_expand *exp)
{
	char	*content;
	t_token	*new_token;

	content = ft_strdup(cur->value);
	if (!content)
	{
		ft_lstclear_token(files, free);
		return;
	}
	new_token = create_token(WORD, content, ft_strlen(content));
	if (!new_token)
	{
		free(content);
		ft_lstclear_token(files, free);
		return;
	}
	ft_lstadd_back_token(exp->tokens, new_token);
}

void *filename_expansion(t_expand *exp, t_shell *sh)
{
    t_token *files;
    t_token *cur;

    exp->buf[exp->buf_i] = '\0';
    files = get_files_list(exp, sh);
    if (!files)
        return (NULL);
    files = pattern_filter(files, exp);
    if (!files)
        return (NULL);
    cur = files;
    while (cur)
    {
        process_file_token(cur, &files, exp);
        cur = cur->next;
    }
    ft_lstclear_token(&files, free);
    exp->has_match = true;
    return (NULL);
}
