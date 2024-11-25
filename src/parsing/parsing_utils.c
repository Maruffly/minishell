/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:10:50 by jbmy              #+#    #+#             */
/*   Updated: 2024/11/22 18:00:39 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	is_separator(t_token_type type)
{
	if (type == PIPE || type == AND || type == OR || type == PAR)
		return (true);
	return (false);
}

void	dup_value(t_token *cur, char **args, int count)
{
	int	i;

	i = 0;
	while (cur && !is_separator(cur->type) && i < count)
	{
		args[i] = ft_strdup(cur->value);
		if (!args[i])
		{
			while (i > 0)
			{
				free(args[i - 1]);
				i--;
			}
			free(args);
			return ;
		}
		i++;
		cur = cur->next;
	}
	args[i] = NULL;
}

char	**token_to_args(t_token *tokens)
{
	t_token	*cur;
	int		count;
	char	**args;

	if (!tokens)
		return (NULL);

	cur = tokens;
	count = 0;
	while (cur && !is_separator(cur->type))
	{
		count++;
		cur = cur->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	cur = tokens;
	dup_value(cur, args, count);
	return (args);
}
