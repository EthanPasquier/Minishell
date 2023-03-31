/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/31 15:33:24 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This func is for > at the front of the comd (Only used if at least 1 cmd)
int	ft_is_last_front(t_token *token, int type)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token->next;
	while (tmp && tmp->type != CMD)
	{
		if (tmp->type == type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void ft_child_redirection_front(t_token *token)
{
	t_token *tmp;
	int fd2;
	
	tmp = token->next;
	while (tmp->type == LESS || tmp->type == GREAT)
	{
		if (tmp->type == LESS)
		{
			fd2 = open(tmp->next->str, O_RDONLY);
			if (fd2 == -1)
				file_does_not_exist(tmp);
		}
		else if (tmp->type == GREAT)
		{
			fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
			if (fd2 == -1)
				ft_error(1); // retourner a la fonction principal pour bien fermer tout les FD.
		}
		if (tmp->type == GREAT && ft_is_last_front(token, GREAT) == 1)
		{
			if (dup2(fd2, STDOUT) == -1)
				ft_error(1); // temp, bad exit			
		}
		if (tmp->type == LESS && ft_is_last_front(token, LESS) == 1)
		{
			if (dup2(fd2, STDIN) == -1)
				ft_error(1); // temp bad exit
		}
		if (tmp->next->next)
		{
			if (tmp->next->next->type == LESS
				|| tmp->next->next->type == GREAT)
			{
				close(fd2);
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	close(fd2);
}