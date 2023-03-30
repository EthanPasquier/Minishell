/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:55:21 by epasquie          #+#    #+#             */
/*   Updated: 2023/03/30 11:43:19 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_wake_word(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static void	*ft_free(char **split, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
		free(split[i++]);
	free(split);
	return (NULL);
}

static char	**ft_fill_substr(char *s, char **str)
{
	size_t	i;
	size_t	j;
	int		b;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	// printf("s = %c\n", s[i]);
	if (s[0] == 29)
	{
		str[0] = ft_substr(s, 0, 2);
		i = 2;
		j = 1;
	}
	while (i <= ft_strlen(s))
	{
		b = 1;
		if (s[i] == '"')
			s[i] = 32;
		if ((ft_wake_word(s[i]) == 0) && index < 0)
			index = i;
		else if (((ft_wake_word(s[i]) == 1) || i == ft_strlen(s)) && index >= 0)
		{
			// if (i <= 1)
			// 	str[j] = ft_substr(s, 0, i);
			// else
			str[j] = ft_substr(s, index, i - index);
			if (!str[j++])
				return (ft_free(str, j));
			if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			{
				while (s[i + b] == '<' || s[i + b] == '>' || s[i + b] == '|'
					|| s[i + b] == 32)
					b++;
				str[j] = ft_substr(s, i, b);
				if (!str[j++])
					return (ft_free(str, j));
			}
			index = -1;
		}
		if (b > 1)
			i += b;
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}

static size_t	count_words(char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s == 0 || s[0] == 0)
		return (0);
	while (s[i])
	{
		if (ft_wake_word(s[i]) == 1)
		{
			while ((ft_wake_word(s[i]) == 1 || s[i] == ' ' || s[i] == 29)
				&& s[i])
				i++;
			count++;
		}
		i++;
	}
	// printf("count = %lu\n", count * 2);
	return (count * 2);
}

char	**ft_split_input(char *s)
{
	char **str;

	str = (char **)malloc((count_words(s) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str = ft_fill_substr(s, str);

	return (str);
}