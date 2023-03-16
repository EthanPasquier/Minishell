/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:40:28 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/08 10:29:18 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_number(char *number)
{
	int	len;
	int	i;

	if (number != NULL)
	{
		i = 0;
		len = ft_strlen(number);
		while (i < len)
		{
			if ((number[i] < '0' || number[i] > '9') && number[i] != '-')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
