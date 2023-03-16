/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:22:59 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/07 17:01:15 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	x;

	i = 0;
	x = ft_strlen(src);
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
		dest[i] = src[i];
		i++;
		}
		dest[i] = '\0';
	}
	return (x);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char src1[] = "Caca1234";
// 	char dst1[] = "Pipi";
// 	char src2[] = "Caca1234";
// 	char dst2[] = "Pipi";
// 	printf("Avant vrai fonction\n");
// 	printf("%s\n", src1);
// 	printf("%s\n\n", dst1);
// 	printf("Après vrai fonction\n");
// 	printf("%lu\n", strlcpy(dst1, src1, strlen(dst1)+1));
// 	printf("%s\n", src1);
// 	printf("%s\n\n", dst1);
// }