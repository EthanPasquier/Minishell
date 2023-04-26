/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:15:48 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/26 03:38:36 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_rmword(char const *str, char const *mots)
{
	size_t	size;
	int		i;
	int		j;
	char	*final;

	if (str == NULL || mots == NULL)
		return (NULL);
	size = ft_strlen(str) - ft_strlen(mots) + 1;
	final = ft_calloc(sizeof(char), size);
	i = 0;
	j = ft_strlen(mots);
	while (i < (int)size)
	{
		final[i] = str[j];
		i++;
		j++;
	}
	return (final);
}

char	*ft_find_var_suite(char *str, char *vars, t_child *child, int a)
{
	char	*new;

	if (vars[0] == '?' && vars[1] == '=' && vars[2] == 0)
	{
		vars = ft_itoa(child->exit_code);
		new = ft_redifine(vars, str, a);
		free(str);
		free(vars);
		return (new);
	}
	else
	{
		new = ft_redifine(" ", str, a);
		free(str);
		return (new);
	}
	return (str);
}

char	*ft_find_var(char *str, char *vars, t_child *child, int a)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (child->init->envp[i])
	{
		if (ft_strncmp(vars, child->init->envp[i], ft_strlen(vars)) == 0)
		{
			vars = ft_rmword(child->init->envp[i], vars);
			new = ft_redifine(vars, str, a);
			free(str);
			free(vars);
			return (new);
		}
		i++;
	}
	if (!new)
		return (ft_find_var_suite(str, vars, child, a));
	return (str);
}

char	*ft_take_var(char *str, int position)
{
	int		i;
	int		nb;
	char	*var;

	i = position;
	while (str[i] != 0)
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '?')
			break ;
		i++;
	}
	if (ft_isalpha(str[i]) == 0 && str[i] != '?')
		i--;
	nb = i - position + 2;
	var = ft_calloc(sizeof(char), nb + 1);
	i = 0;
	while (i < nb - 1)
	{
		var[i] = str[position];
		i++;
		position++;
	}
	var[i] = '=';
	return (var);
}

int	ft_varcount(char *new, int i)
{
	while (new[i] && (new[i] == '?' || ft_isalpha(new[i]) == 1))
		i++;
	return (i);
}
