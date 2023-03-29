/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirections_Great.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/29 14:48:23 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This function is for >
void	ft_multiple_great_front(int *fd2, t_token *tmp)
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

void	ft_child_great_front(t_token *t)
{
	int		fd2;
	t_token	*tmp;

	tmp = t;
	fd2 = -1;
	tmp = tmp->next;
	if (tmp->next->next && tmp->next->next->type == GREAT)
		ft_multiple_great_front(&fd2, tmp);
	else
		fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (dup2(fd2, STDOUT) == -1)
		ft_error(1); // temp, bad exit
	close(fd2);
	// fprintf(stderr, "fd2, STDOUT great_front\n");
}

void ft_child_great_back(t_token *t)
{
	t_token *tmp;
	int fd2;

	tmp = t;
	fd2 = open(tmp->prev->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (dup2(fd2, STDOUT) == -1)
	{
		fprintf(stderr, "dup2 err\n"); // si pas permission ecrire dedans
		ft_error(1); // temp, bad exit
	}
	close(fd2);
	while (tmp->prev->prev && tmp->prev->prev->type == GREAT)
	{
		tmp = tmp->prev->prev;
		if (tmp->prev && tmp->prev->type == FILE)
		{
			fd2 = open(tmp->prev->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
			close(fd2);
		}
		else
			break;
	}
}