/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:34:28 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/09 15:15:23 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* TOUT REFAIRE ET FAIRE ENVIRONNEMENT EN LINKED LIST ? */

// static int	len_equal(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	// fprintf(stderr, "%d\n", i);
// 	return (i);
// }

// char **ft_remove(t_child *child, int n)
// {
// 	int i;
// 	int j;
// 	char **unset;

// 	i = 0;
// 	while (child->envp[i])
// 		i++;
// 	unset = (char **)malloc(sizeof(char *) * i);
// 	if (!unset)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (child->envp[i + 1])
// 	{
// 		if (i != n)
// 		{
// 			unset[j] = (char *)malloc(sizeof(char) * (ft_strlen(child->envp[i]) + 1));
// 			if (unset[j] == NULL)
//             	return (NULL);
// 			ft_strlcpy(unset[j], child->envp[i], ft_strlen(child->envp[i]));
// 			j++;
// 		}
// 		i++;
// 	}
// 	unset[i] = NULL;
// 	return (unset);
// }

// void	ft_unset(t_child *child)
// {
// 	int i;
// 	int k;
// 	char **unset;
	
// 	i = 1;
// 	if (child->cmd[1])
// 	{
// 		while (child->cmd[i])
// 		{
// 			k = 0;
// 			while (child->envp[k])
// 			{
// 				// fprintf(stderr, "%s\n%s\n", child->envp[k], child->cmd[i]);
// 				// fprintf(stderr, "%d\n", ft_strncmp(child->envp[k], child->cmd[i], len_equal(child->envp[k])));
// 				if (ft_strncmp(child->envp[k], child->cmd[i], len_equal(child->envp[k])) == 0)
// 				{
// 					unset = ft_remove(child, k);
// 					ft_free_double(child->envp);
// 					child->envp = unset;
// 					break ;
// 				}
// 				// fprintf(stderr, "---\n");
// 				k++;
// 			}
// 			i++;
// 		}
// 	}
//  }