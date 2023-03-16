/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 08:23:50 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/02 15:52:07 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_char(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*memory;

	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[start] && ft_check_char(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_check_char(s1[end - 1], set))
		end--;
	memory = (char *)malloc(sizeof(*s1) * (end - start) + 1);
	if (!memory)
		return (NULL);
	i = 0;
	while (start < end)
	{
		memory[i] = s1[start];
		i++;
		start++;
	}
	memory[i] = 0;
	return (memory);
}

// #include <stdio.h>
// int main(void)
// {
// 	char a[50] = "fuck les tests fuuuuckkkk";
// 	char b[50] = "fuck";

// 	printf("%s\n", ft_strtrim(a, b));
// }