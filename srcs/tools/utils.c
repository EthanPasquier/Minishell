/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:55:11 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/21 15:23:45 by epasquie         ###   ########.fr       */
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
			break ;
		}
		i++;
	}
	return (path);
}

char	*ft_mini_in_mini(t_child *child)
{
	char	*pwd;
	char	*tmp;
	char	*tmp2;

	pwd = ft_getenv(child->init->envp, "PWD=");
	if (pwd != NULL)
	{
		tmp2 = ft_strtrim(child->cmd[0], ".");
		tmp = ft_strjoin(pwd, tmp2);
		free(tmp2);
		free(pwd);
		if (access(tmp, X_OK | F_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

char	*find_cmd_path(t_child *child)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!child->cmd[0])
		return (NULL);
	if (ft_strncmp(child->cmd[0], "./", 2) == 0)
		return (ft_mini_in_mini(child));
	else if (ft_strncmp(child->cmd[0], "/", 1) == 0)
	{
		if (access(child->cmd[0], X_OK) == 0)
		{
			tmp = ft_strdup(child->cmd[0]);
			return (tmp);
		}
	}
	while (child->all_path[i])
	{
		tmp = ft_strjoin(child->all_path[i], child->cmd[0]);
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
	printf("-----------------\n\n\033[0m");
}
