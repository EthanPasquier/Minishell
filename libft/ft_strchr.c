/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 08:28:35 by jalevesq          #+#    #+#             */
/*   Updated: 2022/10/27 11:15:38 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char string[50] = "teste";
//     int ch = 1024;

//     char string1[50] = "teste";
//     int ch1 = 1024;

//     printf("%s\n", ft_strchr(string, ch));
//     printf("%s\n", strchr(string1, ch1));
// }