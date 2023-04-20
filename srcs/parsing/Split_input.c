/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:55:21 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/20 13:42:03 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_wake_word(char c)
{
	if (c == '|')
		return (1);
	else if (c == '>' || c == '<')
		return (2);
	return (0);
}

int	ft_count_parsing(char *str)
{
	int	i;
	int	count;
	int	tmp;

	i = 0;
	count = 0;
	tmp = 1;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			tmp++;
		if (ft_wake_word(str[i]) >= 1 && tmp % 2 != 0)
		{
			while (ft_wake_word(str[i]) >= 1 || str[i] == 32)
				i++;
			if (i == 0)
				count += 1;
			else
				count += 2;
			if (ft_wake_word(str[i]) == 2)
				count++;
		}
		i++;
	}
	return (count);
}
