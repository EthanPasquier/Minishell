/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:43:10 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/16 09:45:53 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_nbr(t_token *token_list)
{
	t_token *tmp;
	int i;

	tmp = token_list;
	i = 0;
	while (tmp)
	{
		if (tmp->type = CMD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_child()
{
	
}