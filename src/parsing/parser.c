/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:06:27 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/28 20:21:13 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parse_subshell(t_list **token, t_shell *sh)
{
	t_ast	*content;

	if (is_type(token, 1, SUBSHELL_OPEN))
	{
		*token = (*token)->next;
		content = parse_logical(token, sh);
		if (*token && type(*token) == SUBSHELL_CLOSE)
		{
			*token = (*token)->next;
			if ((*token) && is_type(token, 1, WORD))
				return (set_syntax_error(value(*token), sh));
			return (create_ast_subshell(content, sh));
		}
		else if (*token == NULL)
			return (set_syntax_error("\\n", sh));
		else
			return (set_syntax_error(value(*token), sh));
	}
	else if (is_type(token, 1, SUBSHELL_CLOSE))
		return (set_syntax_error(")", sh));
	return (parse_command(token, sh));
}

t_ast	*parse_command(t_list **token, t_shell *sh)
{
	t_list	*tmp;
	int		argc;
	char	**argv;
	int		i;

	tmp = *token;
	argc = 0;
	while (is_type(&tmp, 1, WORD))
	{
		argc++;
		tmp = tmp->next;
	}
	if (argc == 0)
		return (NULL);
	argv = calloc_s((argc + 1), sizeof(char *), PROMPT, sh);
	i = 0;
	while (i < argc)
	{
		argv[i++] = value(*token);
		*token = (*token)->next;
	}
	argv[argc] = NULL;
	return (create_ast_command(argv, sh));
}
