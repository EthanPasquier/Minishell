/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/31 11:24:38 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This func is for > at the front of the comd (Only used if at least 1 cmd)
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

// This func is for > at the back of the cmd (Only used if at least 1 cmd)
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

// This func is for check if > is in front or at the back (If at least 1 cmd)
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