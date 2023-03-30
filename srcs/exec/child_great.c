/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/30 14:09:28 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This function is for >
void	ft_multiple_great_front(int *fd2, t_token *t)
{
	while (t && t->type == GREAT)
	{
		*fd2 = -1;
		*fd2 = open(t->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
		if (t->next && t->next->next && t->next->type == FILE
			&& t->next->next->type == GREAT)
		{
			close(*fd2);
			t = t->next->next;
		}
		else
			break ;
	}	
}

void	ft_child_great_front(t_token *t)
{
	int		fd2;
	t_token	*tmp;

	fd2 = -1;
	tmp = t->next;
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
	// t_token *tmp;
	int fd2;

 	fd2 = open(t->prev->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (dup2(fd2, STDOUT) == -1)
	{
		fprintf(stderr, "dup2 err\n"); // si pas permission ecrire dedans?
		ft_error(1); // temp, bad exit
	}
	close(fd2);
	while (t->prev->prev && t->prev->prev->type == GREAT)
	{
		t = t->prev->prev;
		if (t->prev && t->prev->type == FILE)
		{
			fd2 = open(t->prev->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
			close(fd2);
		}
		else
			break;
	}
}

void	ft_child_great_redirection(t_token *token)
{
	if (token->next && token->next->type == GREAT)
	{
		// fprintf(stderr, "great_front\n");
		ft_child_great_front(token);
	}
	if (token->prev && token->prev->type == FILE
		&& token->prev->prev && token->prev->prev->type == GREAT)
		{
			// fprintf(stderr, "great_back\n");
			ft_child_great_back(token);
		}
}