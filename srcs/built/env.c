/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:45:49 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/14 10:23:03 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_child *child)
{
	int	i;

	i = 0;
	while (child->init->envp[i])
	{
		printf("%s\n", child->init->envp[i]);
		i++;
	}
	return (0);
}
