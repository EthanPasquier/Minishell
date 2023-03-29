/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Child_Redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/29 09:52:05 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	else if (c->i == 0 && t->next && t->next->type == PIPE)
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

// This function is for >
void	ft_multiple_great(int *fd2, t_token *tmp)
{
	while (tmp && tmp->type == GREAT)
	{
		*fd2 = -1;
		*fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
		if (tmp->next && tmp->next->next && tmp->next->type == FILE
			&& tmp->next->next->type == GREAT)
		{
			close(*fd2);
			tmp = tmp->next->next;
		}
		else
			break ;
	}	
}

void	ft_child_great(t_token *t)
{
	int		fd2;
	t_token	*tmp;

	tmp = t;
	fd2 = -1;
	if (t->next && t->next->type == GREAT)
	{
		tmp = tmp->next;
		if (tmp->next->next && tmp->next->next->type == GREAT)
			ft_multiple_great(&fd2, tmp);
		else
			fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
		if (dup2(fd2, STDOUT) == -1)
			ft_error(1); // temp, bad exit
		close(fd2);
		// fprintf(stderr, "fd2, STDOUT\n");
	}
}