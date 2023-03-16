/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:10:19 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/07 16:21:50 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	unsigned int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

// #include <stdio.h>
// int main(void)
// {
// 	char i[50] = "Adam caca";
// 	printf("%zu", ft_strlen(i));
// }