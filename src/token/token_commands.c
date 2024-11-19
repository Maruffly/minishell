/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:16:14 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/15 17:50:14 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/token.h"

int	is_exit_status(char *input)
{
	if (ft_strcmp(input, "$?") == 0)
		return (1);
	return (0);
}

int	is_builtin(char *word)
{
	if (ft_strcmp(word, "cd") == 0 || ft_strcmp(word, "echo") == 0 ||
		ft_strcmp(word, "env") == 0 || ft_strcmp(word, "exit") == 0 ||
		ft_strcmp(word, "export") == 0 || ft_strcmp(word, "pwd") == 0 ||
		ft_strcmp(word, "unset") == 0)
		return (1);
	return (0);
}

int	check_full_path(char *path, char *word)
{
	int		result;
	char	*full_path;

	full_path = ft_strjoin(path, "/");
	if (!full_path)
		return (0);
	full_path = ft_strjoin(full_path, word);
	if (!full_path)
		return (0);
	result = (access(full_path, X_OK) == 0);
	free(full_path);
	return (result);
}

int	is_cmd(char *word)
{
	int		i;
	int		result;
	char	**paths;
	char	*path_env;

	i = 0;
	result = 0;
	path_env = getenv("PATH");
	if (!path_env)
		return (0);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (0);
	while (paths[i] && !result)
	{
		result = check_full_path(paths[i], word);
		i++;
	}
	ft_free_split(paths);
	return (result);
}

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