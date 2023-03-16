/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 09:45:50 by jalevesq          #+#    #+#             */
/*   Updated: 2022/10/26 12:20:08 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (haystack == NULL && len == 0)
		return (NULL);
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (len > 0 && haystack[i] != '\0')
	{
		while (haystack[i + j] == needle[j]
			&& haystack[i + j] != '\0' && len > 0)
		{
			j++;
			len--;
		}
		len += j;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
		len--;
		j = 0;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char big[] = "aaabcabcd";
// 	char little[] = "abcd";

// 	printf("%s\n", ft_strnstr(big, little, 9));
// 	printf("%s\n", strnstr(big, little, 9));
// }
