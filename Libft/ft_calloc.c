/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:48:58 by jmaruffy          #+#    #+#             */
/*   Updated: 2024/06/10 16:33:51 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmb, size_t size)
{
	char	*tab;
	size_t	i;

	if (nmb && size && nmb > UINT_MAX / size)
		return (NULL);
	tab = malloc(nmb * size);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tab[i] = 0;
	}
	return (tab);
}

int	main(void)
{
	int* array;
    int i;

    // Calloc 10 ints
    array = (int *)calloc(0, 0);

	// Check
    if (array == NULL) {
        printf("Échec de l'allocation de mémoire\n");
        return 1;
    }

    // Print values at 0
    for (i = 0; i < 10; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }

    free(array);

    return 0;
}
