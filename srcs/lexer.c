/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:46:12 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/16 11:53:32 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_character(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '-' || c == '"' || c == '$'|| c == '<' || c == '>');
}

static int	ft_compteur(char const *s)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s && s[i])
	{
		if (ft_character(s[i]))
		{
			nb++;
			while (ft_character(s[i]) && s[i])
				i++;
		}
		else
			i++;
	}
	return (nb);
}

static int	ft_taille(char const *s, int i)
{
	int	size;

	size = 0;
	while (ft_character(s[i]) && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free_tab(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

char	**lexer(char const *s)
{
	int		i;
	char	**strs;
	int		size;
	int		j;

	i = 0;
	j = -1;
	strs = (char **)malloc((ft_compteur(s) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (++j < ft_compteur(s))
	{
		while (!ft_character(s[i]))
			i++;
		size = ft_taille(s, i);
		strs[j] = ft_substr(s, i, size);
		if (!(strs[j]))
		{
			ft_free_tab(strs, j);
			return (NULL);
		}
		i += size;
	}
	strs[j] = 0;
	return (strs);
}

// int	main(void)
// {
// 	char input[] = "echo \"salut\"";
// 	char **result;
// 	int count = 0;

// 	result = ft_split(input);
// 	printf("%s\n", result[1]);

// 	return (0);
// }