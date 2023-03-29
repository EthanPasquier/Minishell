/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:42:54 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/29 16:05:22 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_child_pipe(t_child *c, t_token *t, int *fd)
{
	if (t->prev && t->prev->type == PIPE && t->next && t->next->type == PIPE)
	{
		if (dup2(fd[c->j - 1], STDIN) == -1)
			ft_error(1); // temp, bad exit
		if (dup2(fd[c->j], STDOUT) == -1)
			ft_error(1); // temp, bad exit//
		// fprintf(stderr, "ELSE - fd[%d - 1], STDIN\n", c->j);
		// fprintf(stderr, "ELSE - fd[%d], STDOUT\n", c->j);
	}
	else if (c->i == 0 && t->next && t->next->type == PIPE) // Retirer c->i == 0 ?
	{
		if (dup2(fd[c->j], STDOUT) == -1)
			ft_error(1); // temp, bad exit
		// fprintf(stderr, "fd[%d], STDOUT\n", c->j);
	}
	else if (t->prev && t->prev->type == PIPE)
	{
		if (dup2(fd[c->j - 1], STDIN) == -1)
			ft_error(1); // temp, bad exit
		// fprintf(stderr, "fd[%d - 1], STDIN\n", c->j);
	}
}