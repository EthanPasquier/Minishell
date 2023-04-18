/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:12:37 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/17 15:29:29 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_echo(t_child *child)
{
	int	i;

	i = 1;
	while (child->cmd[i])
	{
		printf("%s", child->cmd[i]);
		if (!child->cmd[i + 1])
			printf("\n");
		else
			printf(" ");
		i++;
	}
}

// Ne pas oublier d'uncomment dans builtin_utils pour que ca marche
void	ft_echo(t_child *child)
{
	int	i;

	if (!child->cmd[1])
		printf("\n");
	else if (child->cmd[1] && ft_strncmp(child->cmd[1], "-n", 2) == 0
		&& ft_strlen(child->cmd[1]) == 2)
	{
		i = 2;
		if (child->cmd[i])
		{
			while (child->cmd[i])
			{
				printf("%s", child->cmd[i++]);
				if (child->cmd[i])
					printf(" ");
			}
		}
	}
	else
		ft_print_echo(child);
}
