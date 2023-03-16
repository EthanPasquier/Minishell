/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:04:53 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/01 16:29:51 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*memory;
	size_t	i;

	i = 0;
	memory = malloc(count * size);
	if (memory == NULL)
		return (NULL);
	while (i < count * size)
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}

// #include <stdio.h>
// int main(void)
// {
// 	int *ptr;
// 	ptr = ft_calloc (4, sizeof(int));
// 	if (ptr != NULL)
// 	{
// 	printf (" Memory is created successfully \n");
// 	}
// 	else   
// 	printf (" Memory is not created ");
// 	return 0;
// }