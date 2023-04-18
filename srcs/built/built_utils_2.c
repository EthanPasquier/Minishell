/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:41:01 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/18 08:56:53 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd_dont_exec(t_child *child)
{
	int	fd;

	if (child->cmd[1])
	{
		fd = open(child->cmd[1], O_RDONLY);
		if (fd == -1)
		{
			write(2, "cd: ", 4);
			write (2, child->cmd[1], ft_strlen(child->cmd[1]));
			write (2, ": no such file or directory\n", 28);
			return (1);
		}
		close(fd);
	}
	return (0);
}

void	ft_change_pwd(t_child *child, char *new_cd)
{
	int		i;

	i = 0;
	while (child->init->envp[i]
		&& ft_strncmp(child->init->envp[i], "PWD=", 4) != 0)
		i++;
	if (!child->init->envp[i]
		|| ft_strncmp(child->init->envp[i], "PWD=", 4 != 0))
		return ;
	free(child->init->envp[i]);
	child->init->envp[i] = ft_strjoin("PWD=", new_cd);
}

int	len_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
