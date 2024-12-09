/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:46:34 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/09 14:28:14 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"


int	lexer(char *input, t_token **token_list, t_shell *sh)
{
	t_token			*token;
	t_token_type	type;
	int				i;
	int				len;

	i = 0;
	*token_list = NULL;
	while (input[i])
	{
		len = 0;
		while (is_blank(input[i]))
			i++;
		if (!input[i])
			break ;
		type = get_next_token(input + i, &len, sh);
		if (type == ERROR)
			return (report_synthax_error(sh));
		token = create_token(type, input + i, len);
		if (!token)
			return (report_synthax_error(sh));
		lst_add_back_token(token_list, token);
		i += len;
	}
	return (EXIT_SUCCESS);
}

t_token	*create_token(t_token_type type, char *input, size_t len)
{
	char	*value;
	t_token	*token;

	value = malloc(len + 1);
	if (!value)
		return (NULL);
	ft_strlcpy(value, input, len + 1);
	value[len] = '\0';
	token = init_token(value, type);
	if (!token)
		return (free(value), NULL);
	printf("Token value: %s\n", token->value);
	printf("Token type: %u\n", token->type);
	return (token);
}
