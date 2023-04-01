/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:05:13 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/01 14:47:56 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_next_pipe(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
		return (1);
	return (0);
}

int	ft_is_prev_pipe(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->prev;
	if (tmp && tmp->type == PIPE)
		return (1);
	return (0);

}