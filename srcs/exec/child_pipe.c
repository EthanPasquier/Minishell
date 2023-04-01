/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:42:54 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/01 11:34:45 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_child_pipe(t_child *c, t_token *t)
{
	if (t->prev && t->prev->type == PIPE && t->next && t->next->type == PIPE)
	{
		if ((dup2(c->fd_array[c->j - 1], STDIN) == -1) ||
		(dup2(c->fd_array[c->j], STDOUT) == -1))
			ft_child_error(t, c, ERR_DUP2);
	}
	else if (c->i == 0 && t->next && t->next->type == PIPE) // Retirer c->i == 0 ?
	{
		if (dup2(c->fd_array[c->j], STDOUT) == -1)
			ft_child_error(t, c, ERR_DUP2);
	}
	else if (t->prev && t->prev->type == PIPE)
	{
		if (dup2(c->fd_array[c->j - 1], STDIN) == -1)
			ft_child_error(t, c, ERR_DUP2);
	}
}