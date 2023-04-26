/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redifine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:53:14 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/26 03:38:09 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_redifine_suite(char *str, char *mots, int option, int a)
{
	int	b;
	int	c;
	int	tmp;

	b = 0;
	while (str[a] != '$' && str[a])
		a++;
	c = a + 1;
	while (str[c] != 32 && ft_wake_word(str[c]) == 0 && str[c] != 39
		&& str[c] != 34 && str[c] != '$' && str[c] != 45 && str[c] != 43
		&& str[c])
	{
		c++;
		b++;
	}
	tmp = c;
	c = (ft_strlen(str) - b + ft_strlen(mots));
	if (option == 1)
		return (tmp);
	else if (option == 2)
		return (c);
	else
		return (a);
}

static char	*ft_redifine_suite_v2(char *mots, t_cut cut, char *str, char *new)
{
	int	a;
	int	c;

	a = 0;
	c = ft_strlen(mots);
	while (a < c)
	{
		new[cut.i] = mots[a];
		cut.i++;
		a++;
	}
	a = ft_redifine_suite(str, mots, 1, cut.j);
	while (str[a])
	{
		new[cut.i] = str[a];
		cut.i++;
		a++;
	}
	new[cut.i] = 0;
	return (new);
}

char	*ft_redifine(char *mots, char *str, int w)
{
	int		a;
	t_cut	cut;
	int		c;
	char	*new;

	c = ft_redifine_suite(str, mots, 2, w);
	new = ft_calloc(sizeof(char), c + 1);
	a = ft_redifine_suite(str, mots, 3, w);
	cut.i = 0;
	cut.j = w;
	while (cut.i < a)
	{
		new[cut.i] = str[cut.i];
		cut.i++;
	}
	new = ft_redifine_suite_v2(mots, cut, str, new);
	return (new);
}
