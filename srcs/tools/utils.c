/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:55:11 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/06 12:12:04 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_join(char **path)
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
}

char	**find_path(void)
{
	int		i;
	char	*trim;
	char	**path;

	i = 0;
	path = NULL;
	trim = getenv("PATH");
	path = ft_split(trim, ':');
	ft_join(path);
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