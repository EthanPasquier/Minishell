/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:18:27 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/21 15:35:38 by jalevesq         ###   ########.fr       */
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

char	*ft_suppguillemet(char *new, int tmp, int i, char c)
{
	char	*str;

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
	str = ft_suppspace(new);
	if (ft_strlen(str) < ft_strlen(new))
		free(new);
	new = ft_strdup(str);
	free(str);
	return (new);
}

char	*ft_guillemet(char *str, t_child *child, int k)
{
	t_guill	cut;

	ft_initguill(&cut, str);
	while (str[cut.i])
	{
		if ((str[cut.i] == 39 || str[cut.i] == 34) && cut.tmp == 0)
			ft_markguill(&cut, str);
		else if ((str[cut.i] == cut.c && cut.tmp == 1) || (str[cut.i] == '$'
				&& cut.tmp == 0))
		{
			str = ft_replaceguill(&cut, str, child);
			k++;
		}
		cut.i++;
	}
	if (k > 0)
	{
		free(str);
		str = NULL;
	}
	cut.new = ft_suppguillemet(cut.new, cut.tmp, 0, '\0');
	return (cut.new);
}
