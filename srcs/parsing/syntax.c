/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:06:03 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/31 11:48:53 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include "../../include/minishell.h"

int	ft_error_syntax(char *str)
{
	fprintf(stderr, "\u274C Minishell: '%s' : syntax error\n", str);
	return (1);
}

int	ft_syntax(char *str)
{
	int		i;
	int		temoins;
	char	c;
	int		tmp;

	c = 29;
	i = 0;
	tmp = 0;
	temoins = 0;
	while (str[i])
	{
		if (str[i] == 39)
			tmp++;
		if (str[i] == 34)
			temoins++;
		i++;
	}
	if ((tmp % 2 != 0 || temoins % 2 != 0))
		return (ft_error_syntax(str));
	i = 0;
	tmp = 0;
	temoins = 0;
	while (str[i])
	{
		if (ft_wake_word(str[i]) == 1)
			tmp++;
		if (ft_wake_word(str[i]) == 2)
		{
			temoins++;
			if (str[i] != c && c != 29)
				temoins++;
			c = str[i];
		}
		if (str[i] == 32 && (tmp > 0 || temoins > 0))
			return (ft_error_syntax(str));
		i++;
	}
	if ((tmp >= 2 || temoins > 2) || (tmp > 0 && temoins > 0))
		return (ft_error_syntax(str));
	return (0);
}

// char	*ft_guillemet(char *str)
// {
// 	int i;
//     int tmp;
//     int temoins;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 39)
// 			tmp++;
// 		if (str[i] == 34)
// 			temoins++;
// 		i++;
// 	}
// }