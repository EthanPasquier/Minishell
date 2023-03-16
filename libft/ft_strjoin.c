/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:32:07 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/01 16:26:30 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;
	char	*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = malloc(len);
	if (!ret)
		return (NULL);
	while (i <= len && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (i <= len && *s2)
	{
		ret[i] = *s2;
		i++;
		s2++;
	}
	ret[i] = 0;
	return (ret);
}

// #include <stdio.h>

// int main(void)
// {
// 	char a[25] = "abc";
// 	char b[25] = "def";
// 	printf("%s\n", ft_strjoin(a, b));
// }