/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:45:52 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/10 17:59:02 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd(t_child *child)
{
	char *new_cd;

	if (!child->cmd[1])
	{
		new_cd = ft_getenv(child->init->envp, "HOME=");
        if (new_cd == NULL)
		{
            write(2, "cd: No home directory found\n", 28);
			return ;
		}
	}
	else
		new_cd = child->cmd[1];
	if (chdir(new_cd) == -1)
		perror(new_cd);
	// change pwd
}