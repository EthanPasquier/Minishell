/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:53:20 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/01 15:21:31 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*cstr;
	unsigned char	c2;
	size_t			i;

	i = 0;
	cstr = (unsigned char *)str;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (*cstr == c2)
			return (cstr);
		i++;
		cstr++;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int main(void)
// {
//     char a[50] = "test";
//     int b = 'e';

//     printf("%s\n", ft_memchr(a, b, 5));
//     printf("%s\n", memchr(a, b, 5));
// }
