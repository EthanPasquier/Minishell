/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:00:36 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/07 16:14:36 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	i2;

	i2 = 0;
	if (s != NULL && (*f) != NULL)
	{
		i = ft_strlen(s);
		while (i2 < i)
		{
			(*f)(i2, s);
			i2++;
			s++;
		}
	}
}
