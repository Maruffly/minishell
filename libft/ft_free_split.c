/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:56:20 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/02/11 13:19:23 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **str)
{
	int	i;
	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
