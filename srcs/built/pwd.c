/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:47:01 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/10 17:57:50 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_child *child)
{
	char *pwd;

	pwd = ft_getenv(child->init->envp, "PWD=");
	if (pwd)
		printf("%s\n", pwd);
	else
		perror("minishell: pwd: no path found");
	free(pwd);
}