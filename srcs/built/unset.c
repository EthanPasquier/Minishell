/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:34:28 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/11 15:13:22 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* TOUT REFAIRE ET FAIRE ENVIRONNEMENT EN LINKED LIST ? */

static int	len_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char **ft_remove(t_child *child, int n)
{
    int i;
    int j;
    char **unset;

    i = 0;
    while (child->init->envp[i])
        i++;
    unset = (char **)calloc(sizeof(char *), i + 1);
    if (!unset)
        return (NULL);
    i = -1;
    j = -1;
    while (child->init->envp[++i])
    {
        if (i != n)
        {
            unset[++j] = ft_strdup(child->init->envp[i]);
            if (!unset[j])
                return (NULL);
        }
    }
    unset[j] = NULL;
    return (unset);
}

int	ft_is_remove(t_child *child, int i)
{
	int k;
	char **unset;

	k = 0;
	while (child->init->envp[k])
	{
		if (ft_strncmp(child->init->envp[k], child->cmd[i],
				len_equal(child->init->envp[k])) == 0
			&& len_equal(child->init->envp[k]) == (int)ft_strlen(child->cmd[i]))
		{
			unset = ft_remove(child, k);
			child->init->envp = unset;
			if (!child->init->envp)
			{
				write(2, "child unset error\n", 18);
				return (1);
			}
			break ;
		}
		k++;
	}
	return (0);
}

int ft_unset(t_child *child)
{
	int i;
	int error;
		
	i = 1;
	error = -1;
	if (child->cmd[1])
	{
		while (child->cmd[i])
		{
			error = ft_is_remove(child, i);
			if (error == 1)
				return (1);
			i++;
		}
	}
    return (0);
 }