/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:22:04 by jalevesq          #+#    #+#             */
/*   Updated: 2022/10/26 12:14:44 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	slength;
	size_t	dlength;

	j = 0;
	i = 0;
	if (dest == NULL && dstsize == 0)
		return (ft_strlen(src));
	while (dest[j] != '\0')
		j++;
	dlength = j;
	slength = ft_strlen(src);
	if (dstsize == 0 || dstsize <= dlength)
		return (slength + dstsize);
	while (src[i] != '\0' && j < dstsize - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dlength + slength);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char a[] = "Test";
// 	char b[] = "Nique les tests";
// 	char a1[] = "Test";
// 	char b1[] = "Nique les tests";

// 	printf("Test vrai fonction:\n");
// 	printf("Return value:%lu\n", strlcat(b1, a1, 16));
// 	printf("New b1: %s\n", b1);

// 	printf("Ma fonction:");
// 	printf("Return value:%lu\n", ft_strlcat(b, a, 16))
// }