/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmy <jbmy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:40:46 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/12/13 17:05:40 by jbmy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Fonction pour afficher un nœud de type commande
void print_command(t_ast_command *cmd) {
	if (!cmd || !cmd->args)
		return;
	printf("Command: ");
	for (char **arg = cmd->args; *arg; arg++) {
		printf("%s ", *arg);
	}
	printf("\n");
}

// Fonction pour afficher un nœud de type redirection
void print_redirection(t_ast_redirection *redir) {
	if (!redir)
		return;
	printf("Redirection: %s to file '%s'\n",
		   redir->direction == REDIRECT_OUT ? ">" :
		   redir->direction == REDIRECT_IN ? "<" : "unknown",
		   redir->file);
	if (redir->command) {
		printf("Child of redirection:\n");
		print_ast(redir->command); // Appel récursif sur l'enfant
	}
}

// Fonction pour afficher un nœud de type pipeline
void print_pipeline(t_ast_pipeline *pipeline) {
	if (!pipeline)
		return;
	printf("Pipeline:\n");
	printf("Left:\n");
	print_ast(pipeline->left); // Appel récursif sur la partie gauche
	printf("Right:\n");
	print_ast(pipeline->right); // Appel récursif sur la partie droite
}

// Fonction pour afficher un nœud de type logique (&& ou ||)
void print_logical(t_ast_logical *logical) {
	if (!logical)
		return;
	printf("Logical operation: %s\n",
		logical->operator == AND ? "&&" :
		logical->operator == OR ? "||" : "unknown");
	printf("Left:\n");
	print_ast(logical->left); // Appel récursif sur la partie gauche
	printf("Right:\n");
	print_ast(logical->right); // Appel récursif sur la partie droite
}

// Fonction pour afficher un nœud de type sous-shell
void print_subshell(t_ast_subshell *subshell) {
	if (!subshell || !subshell->child)
		return;
	printf("Subshell:\n");
	print_ast(subshell->child); // Appel récursif sur l'enfant du sous-shell
}

// Fonction pour afficher un nœud de type erreur de syntaxe
void print_syntax_error(t_ast_syntax_error *s_error) {
	if (!s_error || !s_error->unexpected_token)
		return;
	printf("Syntax error: unexpected token '%s'\n", s_error->unexpected_token);
}

// Fonction principale pour afficher un nœud de l'AST
void print_ast(t_ast *node) {
	if (!node)
		return;

	switch (node->type) {
		case AST_COMMAND:
			print_command(&node->u_data.command);
			break;
		case AST_REDIRECTION:
			print_redirection(&node->u_data.redirection);
			break;
		case AST_PIPELINE:
			print_pipeline(&node->u_data.pipeline);
			break;
		case AST_LOGICAL:
			print_logical(&node->u_data.logical);
			break;
		case AST_SUBSHELL:
			print_subshell(&node->u_data.subshell);
			break;
		case AST_SYNTAX_ERROR:
			print_syntax_error(&node->u_data.s_error);
			break;
		default:
			printf("Unknown node type!\n");
			break;
	}
}
