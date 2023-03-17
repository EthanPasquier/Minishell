/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-Utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:55:11 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/17 10:03:52 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char 	**find_path(t_init *init)
{
	int		i;
	char	*tmp;
	char	*trim;
	char	**path;

	i = 0;
	path = NULL;
	while (init->envp[i])
	{
		if (ft_strncmp("PATH=", init->envp[i], 5) == 0)
		{
			trim = ft_strtrim(init->envp[i], "PATH=");
			path = ft_split(trim, ':');
			free(trim);
			i = 0;
			while (path[i])
			{
				tmp = ft_strjoin(path[i], "/");
				free(path[i]);
				path[i++] = tmp;
			}
			break ;
		}
		i++;
	}
	return (path);
}