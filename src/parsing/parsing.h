/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:13:12 by jlaine            #+#    #+#             */
/*   Updated: 2024/11/06 16:15:04 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"



typedef enum s_token
{
	ARG,
	CMD,
	INFILE, 
	OUTFILE, 
	HEREDOC,
	LIMITER, 
	APPEND, // >>
	TRUNCATE, // >
	PIPE, // |
	READ_FROM, // <
}	t_token;


#endif