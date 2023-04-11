/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:45:52 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/10 20:16:19 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_child_pwd(t_child *child)
// {
// 	char *pwd;	
// }

int	ft_cd(t_child *child)
{
	char *new_cd;

	if (!child->cmd[1])
	{
		new_cd = ft_getenv(child->init->envp, "HOME=");
        if (new_cd == NULL)
		{
            write(2, "cd: No home directory found\n", 28);
			return (1);
		}
	}
	else
		new_cd = child->cmd[1];
	if (chdir(new_cd) == -1)
		perror(new_cd);
	return (0);
	// else
	// 	ft_change_pwd(child);
	// changer pwd
}