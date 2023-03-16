/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:14:09 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/07 14:19:53 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n > 0)
	{
		*str = 0;
		str++;
		n--;
	}
}

// #include <stdio.h>
// #include <strings.h>
// int main(void)
// {
// 	char a[50] = "Test";
// 	char b[50] = "Test";

// 	ft_bzero((void *)a + 2, 1);
// 	bzero((void *)b + 2, 1);
// 	printf("%s\n", a);
// 	printf("%s\n", b);
// }