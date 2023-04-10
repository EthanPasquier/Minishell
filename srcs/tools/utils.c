/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:55:11 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/09 22:35:43 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_join(char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i++] = tmp;
	}
	return (path);
}

char	**find_path(t_child *child)
{
	char	*trim;
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (child->init->envp[i])
	{
		if (ft_strncmp("PATH=", child->init->envp[i], 5) == 0)
		{
			trim = ft_strtrim(child->init->envp[i], "PATH=");
			path = ft_split(trim, ':');
			free(trim);
			path = ft_join(path);
			break;
		}
		i++;
	}
	return (path);
}

// void	find_path(t_data *data)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*trim;

// 	i = 0;
// 	while (data->envp[i])
// 	{
// 		if (ft_strncmp("PATH=", data->envp[i], 5) == 0)
// 		{
// 			trim = ft_strtrim(data->envp[i], "PATH=");
// 			data->path = ft_split(trim, ':');
// 			free(trim);
// 			i = 0;
// 			while (data->path[i])
// 			{
// 				tmp = ft_strjoin(data->path[i], "/");
// 				free(data->path[i]);
// 				data->path[i++] = tmp;
// 			}
// 			break ;
// 		}
// 		i++;
// 	}
// }

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

void	ft_title(void)
{
	printf("\033[0;31m\n ███▄ ▄███▓ ██▓ ███▄    █");
	printf("  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    \n");
	printf("▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██");
	printf("    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n");
	printf("▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░");
	printf(" ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n");
	printf("▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ");
	printf("██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n");
	printf("▒██▒   ░██▒░██░▒██░   ▓██░░██░▒████");
	printf("██▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n");
	printf("░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ");
	printf("▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n");
	printf("░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ");
	printf("░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n");
	printf("░      ░    ▒ ░   ░   ░ ░  ▒ ░░ ");
	printf(" ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n");
	printf("       ░    ░           ░  ░  ");
	printf("      ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\n");
	printf("                                     ");
	printf("                                  \n");
	printf("----------------------- \033[0;34mEpa");
	printf("squie & Jalevesq \033[0;31m----------");
	printf("-----------------\n\n");
}