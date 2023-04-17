/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 07:50:52 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/17 08:42:23 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_gnlstrlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_is_newline(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

char	*ft_freegnl(char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (0);
}

char	*ft_strjoin_gnl(char *stash, char *buffer, size_t size)
{
	char	*final;
	size_t	i;
	size_t	j;

	final = malloc(sizeof(char) * (size + 1));
	if (!final)
		return (ft_freegnl(stash, 0));
	i = 0;
	if (stash)
	{
		while (stash[i])
		{
			final[i] = stash[i];
			i++;
		}
	}
	j = 0;
	while (buffer[j])
	{
		final[i + j] = buffer[j];
		j++;
	}
	final[i + j] = '\0';
	free(stash);
	return (final);
}
