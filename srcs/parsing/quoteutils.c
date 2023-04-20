/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoteutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:50:39 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/20 16:02:40 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_initguill(t_guill *cut, char *str)
{
	cut->i = 0;
	cut->place = 0;
	cut->tmp = 0;
	cut->c = '\0';
	cut->new = ft_strdup(str);
}

void	ft_markguill(t_guill *cut, char *str)
{
	cut->place = cut->i;
	cut->c = str[cut->i];
	cut->tmp = 1;
}

void	ft_globvarguill(t_guill *cut, char *str, t_child *child)
{
	if (cut->c != 39 && cut->tmp == 1)
		cut->new = ft_globvar(cut->new, cut->i, child, cut->place + 1);
	else if (str[cut->i] == '$' && cut->tmp == 0)
		cut->new = ft_globvar(cut->new, ft_varcount(cut->new, cut->i + 1),
				child, cut->i);
}

void	ft_reaxguill(t_guill *cut, char *str)
{
	cut->i = ft_varcount(cut->new, cut->i);
	if (ft_where(str, 34, cut->i) >= 0 || ft_where(str, 39, cut->i) >= 0)
		cut->i = ft_varcount(cut->new, cut->i);
	else
		cut->i--;
}

char	*ft_replaceguill(t_guill *cut, char *str, t_child *child)
{
	ft_globvarguill(cut, str, child);
	if (cut->c != 39)
	{
		free(str);
		str = ft_strdup(cut->new);
		ft_reaxguill(cut, str);
	}
	cut->tmp = 0;
	cut->c = '\0';
	return (str);
}
