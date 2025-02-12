/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:22:15 by jlaine            #+#    #+#             */
/*   Updated: 2025/02/12 16:43:14 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void command_expansion(t_ast *node, t_shell *sh)
{
    char    **args;
    int     i;
	char    **expanded_dirs;
	t_token *expanded_args;

	if (!node || !sh || !node->u_data.command.args)
        return;
    expanded_args = NULL;
    args = node->u_data.command.args;
    i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], "*/") == 0)
        {
            expanded_dirs = expand_wildcard_dirs();
            if (expanded_dirs)
                expanded_args = append_tokens_to_list(expanded_args, expanded_dirs);
			ft_free_split(expanded_dirs);
        }
        else
            arg_expansion(args[i], &expanded_args, sh);
		free(args[i]);
        i++;
    }
    free(args);
    node->u_data.command.args = list_to_array(&expanded_args, sh);
    if (expanded_args)
        free_token_list(expanded_args);
}

// OLD
// void	command_expansion(t_ast *node, t_shell *sh)
// {
// 	char	**args;
// 	int		i;
// 	t_token	*expanded_args;

// 	if (!node || !sh || !node->u_data.command.args)
// 		return ;
// 	expanded_args = NULL;
// 	args = node->u_data.command.args;
// 	i = 0;
// 	while (args[i])
// 	{
// 		if (args[i])
// 			arg_expansion(args[i], &expanded_args, sh);
// 		free(args[i]);
// 		i++;
// 	}
// 	free(args);
// 	node->u_data.command.args = list_to_array(&expanded_args, sh);
// 	if (expanded_args)
// 		free_token_list(expanded_args);
// 	if (!node->u_data.command.args)
// 		error("expansion", "failed to convert tokens to array",
// 			EXIT_FAILURE, sh);
// }


void	redirection_expansion(t_ast *node, t_shell *sh)
{
	char	*str;
	t_token	*expanded_args;

	if (!node || !sh || node->u_data.redirection.direction == HEREDOC)
		return ;
	expanded_args = NULL;
	str = node->u_data.redirection.file;
	arg_expansion(str, &expanded_args, sh);
	if (ft_lstsize_token(expanded_args) != 1
		|| !ft_strcmp(expanded_args->value, ""))
		error("wrong redirection", NULL, 1, sh);
	else
		node->u_data.redirection.file = expanded_args->value;
}

t_ast	*node_expansion(t_ast *node, t_shell *sh)
{
	if (!node || !sh)
		return (NULL);
	if (node->type == AST_COMMAND)
		command_expansion(node, sh);
	else if (node->type == AST_REDIRECTION)
		redirection_expansion(node, sh);
	return (node);
}
