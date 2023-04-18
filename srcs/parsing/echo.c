/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:40:59 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/18 10:46:22 by epasquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_echoargument_suite_v3(int tmp, char *str, char *new)
{
	int	i;
	int	nb;

	i = 0;
	nb = tmp;
	while (new[i] && tmp > 1)
	{
		if (ft_issimplearg(new, i))
		{
			new[i] = 29;
			new[i + 1] = 29;
			new[i + 2] = 29;
			tmp--;
		}
		if (new[i] == 32 && tmp < nb && tmp > 1)
			new[i] = 29;
		i++;
	}
	str = ft_suppspace(new);
	return (str);
}

static char	*ft_echoargument_suite_v2(char *str, int j)
{
	char	*new;
	int		i;
	int		tmp;

	new = ft_suppspace(str);
	i = ft_where(new, '-', j) - 1;
	if (i > -1 && ft_issimplearg(new, i) == 0 && ft_isalpha(str[i - 1]) == 0
		&& str[i - 1] != 32)
	{
		return (ft_echoargument(new, i));
	}
	i = 0;
	tmp = 0;
	while (new[i])
	{
		if (ft_issimplearg(new, i) == 1)
			tmp++;
		i++;
	}
	return (ft_echoargument_suite_v3(tmp, str, new));
}

static char	*ft_echoargument_suite(char *str, int i)
{
	int		tmp;
	char	*new;
	int		j;

	tmp = 0;
	new = ft_strdup(str);
	j = i;
	while (str[i] && str[i] != 32)
	{
		if (str[i] == 'n' && str[i - 1] != '-')
		{
			str[i] = 29;
			tmp++;
		}
		else if (str[i] != 'n' && str[i] != 29 && str[i] != 32)
		{
			str = ft_strdup(new);
			break ;
		}
		i++;
	}
	return (ft_echoargument_suite_v2(str, i));
}

char	*ft_echoargument(char *str, int i)
{
	int	tmp;
	int	nb;

	tmp = 0;
	nb = 0;
	while (i >= 0)
	{
		i = ft_where(str, '-', i) - 1;
		if (i > -1 && ft_issimplearg(str, i) == 1)
			i++;
		else
			break ;
		tmp++;
	}
	if (i <= 0 && tmp <= 1)
		return (str);
	i++;
	return (ft_echoargument_suite(str, i));
}
