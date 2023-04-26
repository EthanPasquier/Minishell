/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:34:28 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 06:26:08 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_remove(t_child *child, int n)
{
	int		i;
	int		j;
	char	**unset;

	i = 0;
	while (child->init->envp[i])
		i++;
	unset = (char **)malloc(sizeof(char *) * i);
	if (!unset)
		return (NULL);
	i = 0;
	j = 0;
	while (child->init->envp[i])
	{
		if (i != n)
		{
			unset[j] = ft_strdup(child->init->envp[i]);
			if (!unset[j])
				return (NULL);
			j++;
		}
		i++;
	}
	unset[j] = NULL;
	return (unset);
}

static int	ft_is_remove(t_child *child, int i)
{
	int		k;
	char	**unset;

	k = 0;
	while (child->init->envp[k])
	{
		if (ft_strncmp(child->init->envp[k], child->cmd[i],
				len_equal(child->init->envp[k])) == 0
			&& len_equal(child->init->envp[k]) == (int)ft_strlen(child->cmd[i]))
		{
			unset = ft_remove(child, k);
			ft_free_double(child->init->envp);
			child->init->envp = unset;
			if (!child->init->envp)
				return (1);
			break ;
		}
		k++;
	}
	return (0);
}

int	ft_other_unset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] != '_')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_exception(char *str)
{
	if (ft_only_digit(str) == 0 && ft_other_unset(str) == 0)
		return (0);
	else
	{
		write(2, "minishell: unset: syntax error near \'", 37);
		write(2, str, ft_strlen(str));
		write(2, "\'\n", 2);
		return (1);
	}
	return (0);
}

static void	ft_unset_dont_exec(t_child *child)
{
	int	i;

	i = 1;
	while (child->cmd[i])
	{		
		ft_check_exception(child->cmd[i]);
		i++;
	}
}

int	ft_unset(t_child *child)
{
	int	i;
	int	error;

	i = 1;
	error = -1;
	if (child->cmd[1])
	{
		if (child->cmd_nbr == 1)
		{
			while (child->cmd[i])
			{
				if (ft_check_exception(child->cmd[i]) == 0)
				{
					error = ft_is_remove(child, i);
					if (error == 1)
						return (1);
				}
				i++;
			}
		}
		else
			ft_unset_dont_exec(child);
	}
	return (0);
}
