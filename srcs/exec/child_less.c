/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/30 14:58:59 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void file_does_not_exist(t_token *tmp)
{
	perror(tmp->next->str);
	exit(EXIT_SUCCESS);

}

void	ft_child_less_front(t_token *token)
{
	int fd2;
	
	token = token->next;
	while (token->type == LESS)
	{
		fd2 = open( token->next->str, O_RDONLY);
		if (fd2 == -1)
			file_does_not_exist( token);
		if ( token->next->next
			&&  token->next->next->type == LESS)
		{
			close (fd2);
			 token =  token->next->next;
		}
		else
			 token =  token->next;
	}
	if (dup2(fd2, STDIN) == -1)
		ft_error(1);
	close(fd2);
}

void ft_child_less_back(t_token *token)
{
	int fd2;

	token = token->prev;
	fd2 = -1;
	while (token->prev && token->prev->type == LESS)
	{
		fd2 = open(token->str, O_RDONLY);
		if (fd2 == -1)
			file_does_not_exist(token);
		if (token->next->type == CMD)
		{
			if (dup2(fd2, STDIN) == -1)
				ft_error(1);
		}
		if (token->prev->prev && token->prev->prev->prev
		&& token->prev->prev->prev->type == LESS)
		{
			close (fd2);
			token = token->prev->prev;
		}
		else
			token =  token->prev;
	}
	close(fd2);
}

void	ft_child_less_redirections(t_token *token)
{
	if (token->next && token->next->type == LESS)
		ft_child_less_front(token);
	if (token->prev && token->prev->prev
		&& token->prev->prev->type == LESS)
		ft_child_less_back(token);
	
}