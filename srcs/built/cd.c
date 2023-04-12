/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:45:52 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/12 18:22:09 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_oldpwd(t_child *child, char *old_cd)
{
	int		i;
	char	**old_pwd;
	
	i = 0;
	while (child->init->envp[i])
			i++;
	old_pwd = (char **)malloc(sizeof(char *) * (i + 2));
	if (!old_pwd)
		return ;
	i = 0;
	while (child->init->envp[i])
	{
		old_pwd[i] = ft_strdup(child->init->envp[i]);
		i++;
	}
	old_pwd[i++] = ft_strjoin("OLDPWD=", old_cd);
	old_pwd[i] = NULL;
	ft_free_double(child->init->envp);
	child->init->envp = old_pwd;
}

static void ft_change_oldpwd(t_child *child, char *old_cd)
{
	int i;

	i = 0;
	while (child->init->envp[i]
		&& ft_strncmp(child->init->envp[i], "OLDPWD=", 4) != 0)
		i++;
	if (!child->init->envp[i] || ft_strncmp(child->init->envp[i], "OLDPWD=", 4 != 0))
		ft_oldpwd(child, old_cd);
	else
	{
		free(child->init->envp[i]);
		child->init->envp[i] = ft_strjoin("OLDPWD=", old_cd);
	}
}

static void	ft_change_pwd(t_child *child, char *new_cd)
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

static char	*ft_new_cd(t_child *child)
{
	char *new_cd;

	if (!child->cmd[1])
	{
		new_cd = ft_getenv(child->init->envp, "HOME=");
        if (new_cd == NULL)
		{
            write(2, "cd: No home directory found\n", 28);
			return (NULL);
		}
	}
	else
		new_cd = child->cmd[1];
	return (new_cd);
}

int	ft_cd_dont_exec(t_child *child)
{
	int	fd;

	fd = open(child->cmd[1], O_RDONLY);
	if (fd == -1)
	{
		perror(child->cmd[1]);
		return (1);
	}
	return (0);
}

int	ft_cd(t_child *child)
{
	char *new_cd;
	
	char old_pwd[1024];
	char new_pwd[1024];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (-1);
	new_cd = ft_new_cd(child);
	if (child->cmd_nbr > 1 && ft_cd_dont_exec(child) == 0 && child->cmd[1])
		return (0);
	else if (new_cd && child->cmd_nbr < 2)
	{
		if (chdir(new_cd) == -1)
		{
			perror(new_cd);
			return (1);
		}
		ft_change_oldpwd(child, old_pwd);
		if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
			ft_change_pwd(child, new_pwd);
		return (0);
	}
	return (1);
}