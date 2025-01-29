/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:50:37 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/29 11:02:05 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(void *list)
{
	t_env_list	*env_list;
	t_env_list	*cur;
	t_env_list	*next;

	env_list = (t_env_list *)list;
	if (!env_list)
		return;
	cur = env_list->head;
	while (cur)
	{
		next = cur->next;
		free(cur->var_name);
		free(cur->var_value);
		free(cur);
		cur = next;
	}
	free(env_list);
}

void	ft_lstclear_env(t_env_list **lst, void (*del)(void *))
{
    if (!lst || !*lst || !del)
        return;

    del(*lst);
    *lst = NULL;
}

void	free_env_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	handle_parsing_error(t_shell *sh, t_token *token_lst)
{
	if (sh->parsing_error)
		syntax_error(sh->parsing_error, sh);
	free_token_list(token_lst);
	return (EXIT_FAILURE);
}
