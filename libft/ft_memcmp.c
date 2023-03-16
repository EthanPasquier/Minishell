/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:21:10 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/01 15:49:42 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;
	size_t			i;

	i = 0;
	cs2 = (unsigned char *)s2;
	cs1 = (unsigned char *)s1;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char a[50] = "J'aime la pomme";
// 	char b[50] = "J'aime la glace";

// 	printf(" Ma fonction: %d\n", ft_memcmp(a, b, 50));
// 	printf(" vrai fonction: %d\n", memcmp(a, b, 50));
// }