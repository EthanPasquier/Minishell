/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:44:26 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/20 16:06:12 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_globvar(char *str, int limit, t_child *child, int nb)
{
	char	*mots;
	char	*final;
	int		a;

	mots = NULL;
	final = ft_strdup(str);
	a = ft_where(final, '$', nb);
	while (a > -1 && a <= limit)
	{
		mots = ft_take_var(final, a);
		final = ft_find_var(final, mots, child, a - 1);
		limit += ft_strlen(mots);
		free(mots);
		a = ft_where(final, '$', a + 1);
	}
	free(str);
	return (final);
}

char	*ft_exportsyntax(char *str)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			tmp++;
		if (str[i] == '=' && tmp % 2 != 0)
		{
			if (str[i - 1] == 32 && str[i - 1] != '=')
				str[i - 1] = 29;
			if (str[i + 1] == 32 && str[i - 1] != '=')
				str[i + 1] = 29;
		}
		i++;
	}
	return (str);
}
