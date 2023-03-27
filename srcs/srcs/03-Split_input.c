/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Split_Input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:55:21 by epasquie          #+#    #+#             */
/*   Updated: 2023/03/27 11:24:22 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"

#include "../include/minishell.h"

static void	*ft_free(char **split, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
		free(split[i++]);
	free(split);
	return (NULL);
}

static char	**ft_fill_substr(char const *s, char c, char **str)
{
	size_t	i;
	size_t	j;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if ((s[i] != c && s[i] != '<' && s[i] != '>' && s[i] != '|')
			&& index < 0)
			index = i;
		else if ((s[i] == '<' || s[i] == '>' || s[i] == '|'
					|| i == ft_strlen(s)) && index >= 0)
		{
			str[j] = ft_substr(s, index, i - index);
			if (!str[j++])
				return (ft_free(str, j));
			if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			{
				str[j] = ft_substr(s, i, 1);
				if (!str[j++])
					return (ft_free(str, j));
			}
			index = -1;
		}
		i++;
	}
	str[j] = NULL;
	return (str);
}
static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s == 0 || s[0] == 0)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**split_input(char const *s, char c)
{
	char **str;

	str = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (ft_fill_substr(s, c, str));
}