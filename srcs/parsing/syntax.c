/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:06:03 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/27 09:44:55 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_syntax(char *str)
{
	int	i;
	int	temoins;
	int	tmp;

	i = 0;
	tmp = 0;
	temoins = 0;
	while (str[i])
	{
		// if (str[i] == '-' && ft_isalpha(str[i + 1]) == 0)
		// 	return (ft_error_syntax(str));
		if (str[i] == 39)
			tmp++;
		if (str[i] == 34)
			temoins++;
		i++;
	}
	if ((tmp % 2 != 0 || temoins % 2 != 0))
		return (ft_error_syntax(str));
	if (ft_wake_word(str[0]) == 1)
		return (ft_error_pipe(str, 29));
	if (ft_wake_word(str[0]) == 2)
		return (ft_error_redirection(str));
	return (0);
}

char	*ft_suppspace_suite(int i, int size, char *str)
{
	char	*final;

	final = ft_calloc(sizeof(char), i - size + 1);
	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != 29)
		{
			final[size] = str[i];
			size++;
		}
		i++;
	}
	return (final);
}

char	*ft_suppspace(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == 29)
			size++;
		i++;
	}
	if (size <= 0)
		return (str);
	return (ft_suppspace_suite(i, size, str));
}
