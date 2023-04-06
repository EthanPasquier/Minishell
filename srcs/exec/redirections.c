/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/05 17:55:20 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_mark_count(t_token *token, int type)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == type)
			i += 1;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_less_child(t_child *child, t_token *token, int less)
{
	int		fd;

	fd = -1;
	if (token->type == LESS)
	{
		fd = open(token->next->str, O_RDONLY);
		if (fd == -1)
			ft_child_error(token, child, ERR_OPEN);
		if (less == child->less_mark)
		{
			if (dup2(fd, STDIN) == -1)
			{
				close(fd);
				ft_child_error(token, child, ERR_DUP2);
			}
		}
		close(fd);
	}
}

void	ft_great_child(t_child *child, t_token *token, int great)
{
	int		fd;

	fd = -1;
	if (token->type == GREAT_GREAT)
		fd = open(token->next->str, O_WRONLY | O_APPEND | O_CREAT, 0640);
	else if (token->type == GREAT)
		fd = open(token->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (fd == -1)
		ft_child_error(token, child, ERR_OPEN);
	if (great == child->great_mark)
	{
		if (dup2(fd, STDOUT) == -1)
		{
			close(fd);
			ft_child_error(token, child, ERR_DUP2);
		}
	}
	close(fd);
}
