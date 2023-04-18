/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:45:52 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/18 15:14:27 by jalevesq         ###   ########.fr       */
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

static void	ft_change_oldpwd(t_child *child, char *old_cd)
{
	int	i;

	i = 0;
	while (child->init->envp[i]
		&& ft_strncmp(child->init->envp[i], "OLDPWD=", 4) != 0)
		i++;
	if (!child->init->envp[i]
		|| ft_strncmp(child->init->envp[i], "OLDPWD=", 4 != 0))
		ft_oldpwd(child, old_cd);
	else
	{
		free(child->init->envp[i]);
		child->init->envp[i] = ft_strjoin("OLDPWD=", old_cd);
	}
}

static char	*ft_new_cd(t_child *child)
{
	char	*new_cd;

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

static int	ft_do_cd(char *n_cd, char *o_pwd, t_child *child)
{
	char	new_pwd[1024];

	if (chdir(n_cd) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, n_cd, ft_strlen(n_cd));
		write(2, ": no such file or directory\n", 28);
		if (!child->cmd[1] && n_cd)
			free(n_cd);
		return (1);
	}
	if (!child->cmd[1] && n_cd)
		free(n_cd);
	ft_change_oldpwd(child, o_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
		ft_change_pwd(child, new_pwd);
	return (0);
}

int	ft_cd(t_child *child)
{
	char	*new_cd;
	char	old_pwd[1024];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (-1);
	new_cd = ft_new_cd(child);
	if (child->cmd_nbr > 1)
	{
		if (!child->cmd[1] && new_cd)
		{
			free(new_cd);
			new_cd = NULL;
		}
		if (ft_cd_dont_exec(child) == 0)
			return (0);
		return (1);
	}
	else if (new_cd && child->cmd_nbr < 2)
	{
		if (ft_do_cd(new_cd, old_pwd, child) == 0)
			return (0);
		return (1);
	}
	return (1);
}
