/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:06:03 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/10 12:20:33 by epasquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error_syntax(char *str)
{
	fprintf(stderr, "\u274C Minishell: '%s' : syntax error\n", str);
	return (1);
}

int	ft_error_pipe(char *str)
{
	int		temoins;
	char	c;
	int		i;

	c = 29;
	temoins = 0;
	i = 1;
	if (ft_wake_word(str[i]) > 0)
		return (ft_error_syntax(str));
	while (str[i])
	{
		if (ft_wake_word(str[i]) == 1)
			return (ft_error_syntax("plusieurs pipes"));
		else if (str[i] == 32 && temoins == 0)
			;
		else if ((ft_wake_word(str[i]) == 2) && temoins <= 1)
		{
			temoins++;
			if (str[i] != c && c != 29)
				return (ft_error_syntax("different redirection"));
			c = str[i];
		}
		else
			return (ft_error_syntax("autre"));
		i++;
	}
	if (temoins == 1)
	{
		if (c == '<')
			return (2);
		if (c == '>')
			return (3);
	}
	else if (temoins > 1)
	{
		if (c == '<')
			return (4);
		if (c == '>')
			return (5);
	}
	return (0);
}

int	ft_error_redirection(char *str)
{
	char	c;

	// int		temoins;
	c = str[0];
	// temoins = 0;
	if (ft_wake_word(str[1]) == 1)
		return (ft_error_syntax("pipes"));
	else if (str[1] == 32)
		return (ft_error_syntax("space"));
	else if (ft_wake_word(str[1]) == 2)
	{
		if (str[1] != c)
			return (ft_error_syntax("different redirection"));
	}
	if (ft_strlen(str) > 2)
		return (ft_error_syntax("trop argument"));
	return (0);
}

int	ft_syntax(char *str)
{
	int	i;
	int	temoins;
	int	tmp;

	// char	c;
	// c = 29;
	i = 0;
	tmp = 0;
	temoins = 0;
	while (str[i])
	{
		if (str[i] == '-' && ft_isalpha(str[i + 1]) == 0)
			return (ft_error_syntax(str));
		if (str[i] == 39)
			tmp++;
		if (str[i] == 34)
			temoins++;
		i++;
	}
	if ((tmp % 2 != 0 || temoins % 2 != 0))
		return (ft_error_syntax(str));
	if (ft_wake_word(str[0]) == 1)
		return (ft_error_pipe(str));
	if (ft_wake_word(str[0]) == 2)
		return (ft_error_redirection(str));
	return (0);
}

char	*ft_suppspace(char *str)
{
	int		i;
	int		size;
	char	*final;

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
	final = ft_calloc(sizeof(char), i - size);
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

int	ft_ordreguillemet(char *str)
{
	int		i;
	int		j;
	char	tmp;
	char	c;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		c = 0;
		tmp = 0;
		if (str[i] == 39 || str[i] == 34)
		{
			tmp = str[i];
			while (j > i)
			{
				if (str[j] == 39 || str[j] == 34)
				{
					c = str[j];
					break ;
				}
				j--;
			}
			j--;
			if (tmp != c)
			{
				// printf("tmp = %c\nc = %c\n", tmp, c);
				ft_error_syntax("erreur de guillemets");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*ft_guillemet(char *str, t_child *child)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			break ;
		i++;
	}
	c = str[i];
	str = ft_globvar(str, c, child);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = 29;
		i++;
	}
	str = ft_strtrim(str, " ");
	str = ft_suppspace(str);
	return (str);
}

char	*ft_globvar(char *str, char c, t_child *child)
{
	char *mots;
	int a;

	mots = NULL;
	if (c == 39)
		return (str);
	a = ft_where(str, '$', 0);
	while (a != -1)
	{
		mots = ft_take_var(str, a);
		// printf("mots = %s\n", mots);
		str = ft_find_var(str, mots, child);
		// printf("str = %s|\n", str);
		// return (str);
		free(mots);
		a = ft_where(str, '$', a);
	}
	return (str);
}