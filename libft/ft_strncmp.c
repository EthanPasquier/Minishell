/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:37:42 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/01 16:27:19 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && n > 0 && s1[i] && s2[i])
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char a[] = "test";
// 	char b[] = "text";
// 	printf("%d\n", ft_strncmp(a, b, 9));
// 	printf("%d\n", strncmp(a, b, 9));
// 	return (0);
// }