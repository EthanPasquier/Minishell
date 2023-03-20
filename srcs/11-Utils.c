/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-Utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:55:11 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 10:29:58 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char 	**find_path(char **envp)
{
	int		i;
	char	*tmp;
	char	*trim;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			trim = ft_strtrim(envp[i], "PATH=");
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

char	*find_cmd_path(char **cmd, char **path)
{
	int		i;
	char	*tmp;
	
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd[0]);
		if (access(tmp, X_OK | F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}