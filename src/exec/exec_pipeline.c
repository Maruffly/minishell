/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:05:31 by jlaine            #+#    #+#             */
/*   Updated: 2025/01/16 15:20:05 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void print_pipeline(t_token *pipeline)
{
    t_token *current = pipeline;
    int index = 0;

    printf("=== Pipeline Content ===\n");
    while (current != NULL)
    {
        printf("Token %d:\n", index++);
        printf("  Type: %d\n", current->type); // Affiche le type de token
        printf("  Value: %s\n", current->value); // Affiche la valeur du token (si c'est une chaîne)
        
        // Si le token pointe vers un nœud AST, affiche des informations supplémentaires
        if (current->node != NULL)
        {
            printf("  AST Node Type: %d\n", current->node->type);
            if (current->node->type == AST_COMMAND)
            {
                printf("  Command Args:\n");
                for (int i = 0; current->node->u_data.command.args[i] != NULL; i++)
                {
                    printf("    %s\n", current->node->u_data.command.args[i]);
                }
            }
            else if (current->node->type == AST_PIPELINE)
            {
                printf("  Pipeline Node (left and right)\n");
            }
            else if (current->node->type == AST_REDIRECTION)
            {
                printf("  Redirection: %s -> %s\n", 
                       current->node->u_data.redirection.file,
                       current->node->u_data.redirection.direction == INFILE ? "INFILE" : "OUTFILE");
            }
        }

        current = current->next;
        printf("\n");
    }
    printf("=== End of Pipeline ===\n");
}

t_token	*build_cmd_list(t_ast *node, t_shell *sh)
{
	t_token *pipeline;

	pipeline = NULL;
	while (node->type == AST_PIPELINE)
	{
		add_front_token(&pipeline, node->u_data.pipeline.right, sh);
		if (node->u_data.pipeline.right->type == AST_COMMAND)
			pipeline->value = node->u_data.pipeline.right->u_data.command.args[0];
		if (node->u_data.pipeline.left->type == AST_PIPELINE)
			node = node->u_data.pipeline.left;
		else
		{
			add_front_token(&pipeline, node->u_data.pipeline.left, sh);
			if (node->u_data.pipeline.left->type == AST_COMMAND)
				pipeline->value = node->u_data.pipeline.left->u_data.command.args[0];
			break;
		}
	}
	return (pipeline);
}

int	execute_pipeline_token(t_token *pipeline, t_shell *sh)
{
	int		p[2];
	pid_t	last_pid;
	int		n_pipeline;
	int		prev_read_end;
	int		last_cmd_status;

	n_pipeline = ft_lstsize_token(pipeline) - 1;
	last_pid = 0;
	prev_read_end = -1;
	while (pipeline)
	{
		pipe(p);
		last_pid = exec_one_pipeline_token(pipeline, prev_read_end, p, sh);
		setup_for_next_command(&prev_read_end, p, sh);
		pipeline = pipeline->next;
	}
	last_cmd_status = wait_for_children(last_pid, n_pipeline, sh);
	return (last_cmd_status);
}

int	exec_pipeline(t_ast *node, t_shell *sh)
{
	t_token *pipeline;

	pipeline = build_cmd_list(node, sh);
	/* print_pipeline(pipeline); */
	return (execute_pipeline_token(pipeline, sh));
}
