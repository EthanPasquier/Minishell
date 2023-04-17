/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_caps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:29:58 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/17 08:41:23 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_caps(const char *s1, const char *s2, size_t n)
{
	char	*s1_upper;
	char	*s2_upper;
	int		result;
	size_t	i;

	i = -1;
	s1_upper = ft_strdup(s1);
	s2_upper = ft_strdup(s2);
	if (s1_upper == NULL || s2_upper == NULL)
		return (-1);
	while (++i < n && s1_upper[i] && s2_upper[i])
	{
		s1_upper[i] = ft_toupper(s1_upper[i]);
		s2_upper[i] = ft_toupper(s2_upper[i]);
	}
	result = ft_strncmp(s1_upper, s2_upper, n);
	free(s1_upper);
	free(s2_upper);
	return (result);
}
