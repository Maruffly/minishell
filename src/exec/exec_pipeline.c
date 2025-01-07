/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:05:31 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/07 18:08:07 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int exec_pipeline(t_ast *node, t_shell *sh)
{
    t_token *pipeline;

    pipeline = build_cmd_list(node, sh); /////// TO DO 
    return (execute_pipeline_list(pipeline, sh)); ///// TO DO
}


