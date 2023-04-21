/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:34:03 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/21 15:35:54 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_chevronparsing(char *str, int i)
{
	while (str[i] == 32)
		i++;
	while ((ft_wake_word(str[i]) > 0 || str[i] == 32) && str[i])
		i++;
	while ((ft_wake_word(str[i]) == 0 && str[i] != 32 && str[i] != 29)
		&& str[i])
		i++;
	if (i < (int)ft_strlen(str) && ft_wake_word(str[i]) == 0)
		str[i] = 29;
	return (str);
}

static char	*ft_write_cut_str(char *str)
{
	int		count;
	char	*output;

	count = ft_count_parsing(str);
	output = ft_calloc(sizeof(char), (ft_strlen(str) + count) + 1);
	return (output);
}

static t_cut	*ft_write_cut_suite_v2(t_cut *cut)
{
	if (ft_wake_word(cut->str[cut->i]) == 2)
		cut->str = ft_chevronparsing(cut->str, cut->i + 1);
	if (cut->i > 0)
	{
		cut->output[cut->j] = 29;
		cut->j++;
	}
	while (ft_wake_word(cut->str[cut->i]) >= 1 || cut->str[cut->i] == 32)
	{
		if (ft_wake_word(cut->str[cut->i]) == 2)
			cut->str = ft_chevronparsing(cut->str, cut->i + 1);
		cut->output[cut->j] = cut->str[cut->i];
		cut->j++;
		cut->i++;
	}
	cut->output[cut->j] = 29;
	return (cut);
}

static t_cut	*ft_write_cut_suite(t_cut *cut)
{
	if (cut->str[cut->i] == 39 || cut->str[cut->i] == 34)
		cut->tmp++;
	if (ft_wake_word(cut->str[cut->i]) >= 1 && cut->tmp % 2 != 0)
		cut = ft_write_cut_suite_v2(cut);
	else
	{
		cut->output[cut->j] = cut->str[cut->i];
		cut->i++;
	}
	cut->j++;
	return (cut);
}

char	**ft_write_cut(char *str)
{
	t_cut	*cut;
	char	*output;
	char	**abc;

	cut = malloc(sizeof(t_cut));
	cut->i = 0;
	cut->j = 0;
	cut->tmp = 1;
	cut->output = ft_write_cut_str(str);
	cut->str = ft_strdup(str);
	while (cut->str[cut->i])
	{
		cut = ft_write_cut_suite(cut);
	}
	output = ft_strdup(cut->output);
	free(cut->str);
	free(cut->output);
	free(cut);
	abc = ft_split_parser(output, 29);
	free(output);
	return (abc);
}
