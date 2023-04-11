/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:34:28 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/10 20:11:55 by jalevesq         ###   ########.fr       */
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
    {
        fprintf(stderr, "MALLOC ERROR UNSET");    
        return (NULL);
    }
    i = 0;
    j = 0;
    while (child->init->envp[i])
    {
        if (i != n)
        {
            unset[j] = (char *)malloc(sizeof(char) * (ft_strlen(child->init->envp[i]) + 1));
            if (!unset[j])
            {
                fprintf(stderr, "MALLOC ERROR UNSET J");
                return (NULL);
            }
            ft_strlcpy(unset[j], child->init->envp[i], ft_strlen(child->init->envp[i]) + 1);
            j++;
        }
        i++;
    }
    unset[j] = NULL; // terminate the array with a NULL pointer
    return (unset);
}

int ft_unset(t_child *child)
{
	int i;
	int k;
	char **unset;
	
	i = 1;
	if (child->cmd[1])
	{
		while (child->cmd[i])
		{
			k = 0;
			while (child->init->envp[k])
			{
				if (ft_strncmp(child->init->envp[k], child->cmd[i], len_equal(child->init->envp[k])) == 0)
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
			i++;
		}
	}
    return (0);
 }