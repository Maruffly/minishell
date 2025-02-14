/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:11 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/14 15:07:41 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

char	*get_path_env(t_env_list *env)
{
	t_env_list	*path_node;

	path_node = find_env_node(env, "PATH");
	if (!path_node || !path_node->var_value)
	{
		ft_putstr_fd("minishell: PATH not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (path_node->var_value);
}

static void	add_env_node_from_envp(t_env_list *list, char *envp_line)
{
	size_t	name_len;
	char	*var_name;
	char	*var_value;

	name_len = ft_strchr(envp_line, '=') - envp_line;
	var_name = ft_substr(envp_line, 0, name_len);
	var_value = ft_strdup(ft_strchr(envp_line, '=') + 1);
	if (!var_name || !var_value)
	{
		free(var_name);
		free(var_value);
		ft_lstclear_env(&list, free_env_list);
		return ;
	}
	add_env_node(list, var_name, var_value);
	free(var_name);
	free(var_value);
}

static t_env_list	*init_env_list(void)
{
	t_env_list	*list;

	list = ft_calloc(1, sizeof(t_env_list));
	if (!list)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	list->next = NULL;
	return (list);
}

t_env_list	*init_envp(char **envp)
{
	int			i;
	t_env_list	*list;

	list = init_env_list();
	if (!list)
		return (NULL);
	if (!envp || !envp[0])
		return (list);
	i = -1;
	while (envp[++i])
		add_env_node_from_envp(list, envp[i]);
	return (list);
}

void	init_shell(t_shell *sh, char **envp)
{
	sh->is_parent = true;
	sh->prompt_mode = MAIN_PROMPT;
	sh->last_status = EXIT_SUCCESS;
	sh->env = init_envp(envp);
	sh->parsing_error = NULL;
	sh->must_exit = false;
	if (envp && envp[0])
		shell_level(sh);
}
