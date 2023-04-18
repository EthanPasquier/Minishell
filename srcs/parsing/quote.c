/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:18:27 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/18 15:53:35 by epasquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_ordreguillemet(char *str)
{
	int		i;
	char	c;
	int		tmp;

	i = 0;
	c = 29;
	tmp = 0;
	while (str[i])
	{
		if ((str[i] == 39 || str[i] == 34) && tmp == 0)
		{
			c = str[i];
			tmp = 1;
		}
		else if ((str[i] == c && tmp == 1))
			tmp = 0;
		i++;
	}
	if (tmp == 1)
		return (ft_error_syntax("erreur de guillemets"));
	return (0);
}

char	*ft_suppguillemet(char *new, int tmp)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	tmp = 0;
	while (new[i])
	{
		if ((new[i] == 39 || new[i] == 34) && tmp == 0)
		{
			c = new[i];
			new[i] = 29;
			tmp = 1;
		}
		else if (new[i] == c && tmp == 1)
		{
			new[i] = 29;
			tmp = 0;
		}
		i++;
	}
	new[i] = 0;
	return (new);
}

char	*ft_guillemet(char *str, t_child *child, int k)
{
	int		i;
	char	*new;
	int		tmp;
	int		place;
	char	c;

	i = 0;
	place = 0;
	tmp = 0;
	c = '\0';
	new = ft_strdup(str);
	while (str[i])
	{
		if ((str[i] == 39 || str[i] == 34) && tmp == 0)
		{
			place = i;
			c = str[i];
			tmp = 1;
		}
		else if ((str[i] == c && tmp == 1) || (str[i] == '$' && tmp == 0))
		{
			if (c != 39 && tmp == 1)
				new = ft_globvar(new, i, child, place + 1);
			else if (str[i] == '$' && tmp == 0)
				new = ft_globvar(new, ft_varcount(new, i + 1), child, i);
			if (c != 39)
			{
				free(str);
				str = ft_strdup(new);
				i = ft_varcount(new, i);
				if (ft_where(str, 34, i) >= 0 || ft_where(str, 39, i) >= 0)
					i = ft_varcount(new, i);
				else
					i--;
			}
			tmp = 0;
			k++;
			c = '\0';
		}
		i++;
	}
	if (k > 0)
	{
		free(str);
		str = NULL;
	}
	new = ft_suppguillemet(new, tmp);
	return (new);
}
