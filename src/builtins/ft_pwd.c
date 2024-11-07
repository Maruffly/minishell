/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:18:25 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/11/07 18:19:08 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void minishell_cd(char **args) {
    // Vérifier que l'utilisateur a fourni un argument
    if (!args[1]) {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }

    // Vérifier si le chemin est absolu ou relatif
    if (args[1][0] == '/' || strncmp(args[1], "./", 2) == 0 || strncmp(args[1], "../", 3) == 0 || strcmp(args[1], ".") == 0 || strcmp(args[1], "..") == 0) {
        // Tenter de changer de répertoire
        if (chdir(args[1]) == -1) {
            // Si chdir échoue, afficher une erreur
            fprintf(stderr, "cd: %s: %s\n", args[1], strerror(errno));
        }
    } else {
        fprintf(stderr, "cd: only relative or absolute paths are allowed\n");
    }
}
