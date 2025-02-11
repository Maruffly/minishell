/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wildcards_dirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:43:26 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/11 17:22:06 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_directory(char *name)
{
	DIR	*dir;

	dir = opendir(name);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

static char	*append_slash(char *name)
{
    char	*new_name;
    int		len;

	len = ft_strlen(name);
	new_name = malloc(len + 2);
	if (!new_name)
		return (NULL);
	ft_strcpy(new_name, name);
	new_name[len] = '/';
	new_name[len + 1] = '\0';
	return (new_name);
}

static char	**ft_realloc_add(char **array, char *new_str)
{
	int		i;
    char	**new_array;

	if (!new_str)
		return (array);
	i = 0;
	while (array && array[i])
		i++;
	new_array = ft_calloc(i + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new_array[i] = array[i];  // Copie les anciens éléments
		i++;
	}
	new_array[i] = ft_strdup(new_str); // Ajoute le nouvel élément
	new_array[i + 1] = NULL; // S'assure que le tableau reste NULL-terminé
	free(array); // Libère l'ancien tableau
	return (new_array);
}

char	**expand_wildcard_dirs(void)
{
    DIR *dir;
    struct dirent *entry;
    char **result;
    char *tmp;
    
    dir = opendir(".");
    if (!dir)
        return (NULL);
    result = ft_calloc(1, sizeof(char *));
    if (!result)
        return (NULL);
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] != '.' && is_directory(entry->d_name))
        {
            tmp = append_slash(entry->d_name);
            if (tmp)
                result = ft_realloc_add(result, tmp);
        }
    }
    closedir(dir);
    return (result);
}

t_token	*append_tokens_to_list(t_token *list, char **to_add)
{
	int		i;
	t_token	*new_token;
	t_token	*last;

	if (!to_add)
		return (list);
	i = 0;
	last = list;
	while (last && last->next)
		last = last->next;
	while (to_add[i])
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (list);
		new_token->value = ft_strdup(to_add[i]);
		new_token->next = NULL;
		if (!list)
			list = new_token;
		else
			last->next = new_token;
		last = new_token;
		i++;
	}
	return (list);
}
