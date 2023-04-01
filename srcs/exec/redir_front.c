/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/01 11:35:05 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This func is for > at the front of the comd (Only used if at least 1 cmd)
// wtf ca fait aucun sens cette fonction et la facon quelle est utilise. J'ai dev quoi la ? Pourquoi ca marche ?> 
int	ft_is_last_front(t_token *token, int type)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != CMD)
	{
		if (tmp->type == type)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int ft_open_front(t_token *tmp, t_child *c)
{
	int fd2;

	fd2 = -1;
	if (tmp->type == LESS)
	{
		fd2 = open(tmp->next->str, O_RDONLY);
		if (fd2 == -1)
			ft_child_error(tmp, c, ERR_OPEN);
	}
	else if (tmp->type == GREAT)
	{
		fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
		if (fd2 == -1)
			ft_child_error(tmp, c, ERR_OPEN);
	}
	return (fd2);
}

void ft_is_last_redir(t_token *tmp, t_token *t, int *fd2, t_child *c)
{
	if (tmp->type == GREAT && ft_is_last_front(t, GREAT) == 1)
	{
		if (dup2(*fd2, STDOUT) == -1)
		{
			close(*fd2);
			ft_child_error(tmp, c, ERR_DUP2);
		}	
	}
	if (tmp->type == LESS && ft_is_last_front(t, LESS) == 1)
	{
		if (dup2(*fd2, STDIN) == -1)
		{
			close(*fd2);
			ft_child_error(tmp, c, ERR_DUP2);
		}
	}
}

void ft_child_redirection_front(t_token *token, t_child *c)
{
	t_token *tmp;
	int fd2;
	
	tmp = token->next;
	while (tmp->type == LESS || tmp->type == GREAT)
	{
		fd2 = ft_open_front(tmp, c);
		ft_is_last_redir(tmp, token, &fd2, c);
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