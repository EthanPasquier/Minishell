/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:05:10 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/08 11:23:13 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned	int, char))
{
	int		i;
	int		i2;
	char	*buffer;

	if (s == NULL || f == NULL)
		return (NULL);
	i2 = 0;
	i = ft_strlen(s);
	buffer = (char *)malloc(sizeof(char) * i + 1);
	if (!buffer)
		return (NULL);
	while (i2 < i)
	{
		buffer[i2] = (*f)(i2, s[i2]);
		i2++;
	}
	buffer[i2] = '\0';
	return (buffer);
}

// char	ft_touppers(unsigned int c, char i)
// {
// 	(void)c;
// 	if (i >= 97 && i <= 122)
// 		i -= 32;
// 	return (i);
// }

// #include <stdio.h>
// int main(void)
// {
// 	char c[50] = "test";
// 	int i = 0;
// 	int j = 0;

// 	printf("%s", ft_strmapi(c, ft_touppers));
// }