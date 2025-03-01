/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:36:46 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 10:09:40 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path(char *path_to, char *file, t_shell *sh)
{
	char	*slash_path;
	char	*full_path;

	slash_path = safe_strjoin(path_to, "/", PROMPT, sh);
	full_path = safe_strjoin(slash_path, file, PROMPT, sh);
	return (full_path);
}

static bool	contain_current_dir_symbol(char *paths)
{
	if (!paths)
		return (false);
	if (paths[0] == ':' || paths[ft_strlen(paths) - 1] == ':')
		return (true);
	if (ft_strnstr(paths, "::", ft_strlen(paths)) != NULL)
		return (true);
	return (false);
}

char	**build_paths_array(t_shell *sh)
{
	char	**paths_array;
	char	*paths;

	paths_array = NULL;
	paths = value(env_var("PATH", sh->env));
	if (!paths)
		paths = safe_strdup(":", PROMPT, sh);
	paths_array = safe_split(paths, ':', PROMPT, sh);
	if (contain_current_dir_symbol(paths))
		add_arg_to_array(&paths_array, safe_strdup(".", PROMPT, sh), sh);
	return (paths_array);
}
