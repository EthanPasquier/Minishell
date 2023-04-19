/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:40:59 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/19 17:48:41 by epasquie         ###   ########.fr       */
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
			if (str[i] != 32)
				return (tmp);
			nb = i - 1;
		}
		i++;
	}
	return (nb);
}

char	*ft_resizeecho(char *str, int i, int nb)
{
	char	*new;
	int		j;

	j = 0;
	new = ft_calloc(sizeof(char), ft_strlen(str) - (nb - i));
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	new[j] = '-';
	j++;
	new[j] = 'n';
	i = nb;
	j++;
	while (i < (int)ft_strlen(str))
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = 0;
	str = ft_strdup(new);
	free(new);
	return (str);
}

char	*ft_echoargument(char *str, int i)
{
	int		tmp;
	char	*new;
	int		nb;

	tmp = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '-')
			break ;
		i++;
	}
	nb = ft_echoargument_suite(i, str);
	if (i >= nb)
		return (str);
	new = ft_resizeecho(str, i, nb + 1);
	str = ft_strdup(new);
	free(new);
	return (str);
}
