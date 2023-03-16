/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:06:46 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/01 15:59:09 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = b;
	while (len > 0)
	{
		*str = c;
		str++;
		len--;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char a[50] = "Le test";
// 	char b[50] = "Le test";

// 	printf("%s\n", ft_memset((void *)a + 2, 'g', 4));
// 	printf("%s\n", memset((void *)a + 2, 'g', 4));
// }