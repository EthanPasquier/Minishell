/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:42:50 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/20 13:42:49 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error_syntax(char *str)
{
	fprintf(stderr, "\u274C Minishell: '%s' : syntax error\n", str);
	return (1);
}

int	ft_error_pipe_suite(int temoins, char c)
{
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

int	ft_error_pipe(char *str, char c)
{
	int	temoins;
	int	i;

	temoins = 0;
	i = 0;
	if (ft_wake_word(str[1]) > 0)
		return (ft_error_syntax(str));
	while (str[++i])
	{
		if (ft_wake_word(str[i]) == 1)
			return (ft_error_syntax("plusieurs pipes"));
		else if (str[i] == 32 && temoins == 0)
			;
		else if ((ft_wake_word(str[i]) == 2) && temoins <= 1)
		{
			temoins++;
			if (c != 29 && str[i] != c)
				return (ft_error_syntax("different redirection"));
			c = str[i];
		}
		else
			return (ft_error_syntax("autre"));
	}
	return (ft_error_pipe_suite(temoins, c));
}

int	ft_error_redirection(char *str)
{
	char	c;

	c = str[0];
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
