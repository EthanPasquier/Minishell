/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 05:42:10 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 06:25:46 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_only_digit(char *str)
{
	int	i;
	int	forbiden;

	i = 0;
	forbiden = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) == 1)
			forbiden++;
		else if (str[i] != '_' && ft_isalpha(str[i]) != 1)
			forbiden++;
		i++;
	}
	if (forbiden == len_equal(str))
		return (1);
	return (0);
}

static int	ft_other_than_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] != '_')
				return (1);
		}
		i++;
	}
	if (str[i] && str[i] == '=')
		return (0);
	return (1);
}

int	ft_digit_equal(char *str)
{
	int	flag;

	flag = 0;
	flag += ft_only_digit(str);
	flag += ft_other_than_alnum(str);
	if (flag > 0)
		return (1);
	return (0);
}
