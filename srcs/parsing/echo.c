/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:40:59 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/26 03:37:52 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echoargument_suite(int i, char *str)
{
	int	nb;
	int	tmp;

	nb = i;
	while (str[i])
	{
		if (str[i] == '-')
		{
			tmp = i - 1;
			i++;
			while (str[i] == 'n')
				i++;
			if (str[i] && str[i] != 32 && i < (int)ft_strlen(str))
				return (tmp);
			nb = i - 1;
		}
		else if (str[i] != 32)
			return (nb);
		if (i < (int)ft_strlen(str))
			i++;
	}
	return (nb);
}

char	*ft_resizeecho(char *str, int i, int nb)
{
	int		j;
	int		num;
	char	*new;

	num = ft_strlen(str) - (nb - i) + 3;
	new = ft_calloc(sizeof(char), num);
	j = 0;
	while (j <= i + 1)
	{
		new[j] = str[j];
		j++;
	}
	new[j] = 32;
	i = nb + 1;
	j++;
	while (i < (int)ft_strlen(str) && j < num)
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}

char	*ft_echoargument(char *str, int i)
{
	char	*new;
	int		nb;

	nb = 0;
	while (str[i])
	{
		if (str[i] == '-')
			break ;
		i++;
	}
	nb = ft_echoargument_suite(i, str);
	if (i >= nb - 1)
		return (str);
	new = ft_resizeecho(str, i, nb);
	str = ft_strdup(new);
	free(new);
	return (str);
}
