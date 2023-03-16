/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:44:36 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/02 15:51:24 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_loop(void *dst, const void *src, size_t i, size_t len)
{
	unsigned char	*cdst;
	unsigned char	*csrc;

	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	while (i < len)
	{
		cdst[i] = csrc[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*csrc;
	char	*cdst;

	i = 0;
	csrc = (char *)src;
	cdst = (char *)dst;
	if (!(dst || src))
		return (NULL);
	if (cdst > csrc)
	{
		while (i < len)
		{
			cdst[len - 1] = csrc[len - 1];
			len--;
		}
	}
	else
	{
		ft_loop(cdst, csrc, i, len);
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char str1[50] = "123456";
//     char str2[50] = "123456";

//     ft_memcpy(str1+1, str1, 6);
//     memmove(str2+1, str2, 6);

//     printf("%s\n", str1);
//     printf("%s\n", str2);
// }