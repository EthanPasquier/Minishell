/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:06:18 by jalevesq          #+#    #+#             */
/*   Updated: 2022/10/25 15:03:08 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*csrc;
	char	*cdst;

	i = 0;
	csrc = (char *)src;
	cdst = (char *)dst;
	if (!(dst || src))
		return (NULL);
	while (i < n)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}

// #include <string.h>
// #include <stdio.h>

// int main(void)
// {
//     char str1[50] = "123456";
//     char str2[50] = "123456";

//     ft_memcpy(str1+1, str1, 6);
//     memmove(str2+1, str2, 6);

//     printf("%s\n", str1);
//     printf("%s\n", str2);
// }
