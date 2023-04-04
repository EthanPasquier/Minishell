/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:09:11 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/04 09:17:46 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_mark_count(t_token *token, int type)
{
	t_token *tmp;
	int i;

	i = 0;
	tmp = token;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	while(tmp && tmp->type != PIPE)
	{
		if (tmp->type == type)
			i += 1;
		tmp = tmp->next;
	}
	return (i);
}
