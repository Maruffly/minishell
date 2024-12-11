/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:16:14 by jlaine            #+#    #+#             */
/*   Updated: 2024/12/10 15:30:14 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"


int	is_builtin(char *word)
{
	if (ft_strcmp(word, "cd") == 0 || ft_strcmp(word, "echo") == 0 ||
		ft_strcmp(word, "env") == 0 || ft_strcmp(word, "exit") == 0 ||
		ft_strcmp(word, "export") == 0 || ft_strcmp(word, "pwd") == 0 ||
		ft_strcmp(word, "unset") == 0)
		return (1);
	return (0);
}

/* bool	is_word(t_token *token)
{
	if (token->type == )
} */

/* void	init_command_array(t_command *cmd, char *input)
{
	int		pos;
	int		word_idx;

	word_idx = 0;
	pos = 0;
	while (input[pos])
	{
		skip_whitespace(input, &pos);
		if (input[pos])
		{
			cmd->command[word_idx] = extract_word(input, pos);
			if (!cmd->command[word_idx])
			{
				perror("Fail to extract word");
				break ;
			}
			printf(" - %s\n", cmd->command[word_idx]);
			word_idx++;
			pos += ft_strlen(cmd->command[word_idx - 1]);
		}
	}
	cmd->command[word_idx] = NULL;
} */
