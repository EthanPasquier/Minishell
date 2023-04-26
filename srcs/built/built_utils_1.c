/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:27:48 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 05:52:56 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_if_29(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 29)
			return (1);
		i++;
	}
	return (0);
}

int	ft_does_it_exist(int i, int j, char **export, t_child *child)
{
	int	n;

	n = 0;
	while (n < i)
	{
		if (ft_strncmp(export[n], child->cmd[j], len_equal(child->cmd[j])) == 0)
			return (n);
		n++;
	}
	return (-1);
}

void	sort_env_alph(char **env_copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strncmp(env_copy[i], env_copy[j], 255) > 0)
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
			j++;
		}
	}
}

int	ft_export_nbr(t_child *child)
{
	int	j;
	int	export_nbr;

	j = 1;
	export_nbr = 0;
	while (child->cmd[j])
	{
		if (ft_check_if_29(child->cmd[j]) == 0
			&& ft_digit_equal(child->cmd[j]) == 0)
			export_nbr++;
		else
		{
			write(2, "minishell: export: ", 19);
			write(2, child->cmd[j], ft_strlen(child->cmd[j]));
			write(2, ": not a valid identifier\n", 25);
		}
		j++;
	}
	return (export_nbr);
}
