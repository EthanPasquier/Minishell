/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/17 15:34:05 by jalevesq         ###   ########.fr       */
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

static void	ft_less_child(t_child *c, t_token *tmp, int less)
{
	int		fd;

	fd = -1;
	if (tmp->type == LESS)
	{
		fd = open(tmp->next->str, O_RDONLY);
		if (fd == -1)
			ft_child_error(tmp, c, ERR_OPEN_LESS);
		if (less == c->less_mark)
		{
			if (dup2(fd, STDIN) == -1)
			{
				close(fd);
				ft_child_error(tmp, c, ERR_DUP2);
			}
		}
		close(fd);
	}
}

static void	ft_great_child(t_child *child, t_token *token, int great)
{
	int		fd;

	fd = -1;
	if (token->type == GREAT_GREAT)
		fd = open(token->next->str, O_WRONLY | O_APPEND | O_CREAT, 0640);
	else if (token->type == GREAT)
		fd = open(token->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (fd == -1)
		ft_child_error(token, child, ERR_OPEN_GREAT);
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

void	ft_less_n_great(t_child *child, t_token *tmp)
{
	t_token	*tmp2;
	int		great;
	int		less;

	tmp2 = tmp;
	great = 0;
	less = 0;
	while (tmp2 && tmp2->type != PIPE)
	{
		if (tmp2->type == GREAT || tmp2->type == GREAT_GREAT)
		{
			great++;
			ft_great_child(child, tmp2, great);
		}
		else if (tmp2->type == LESS)
		{
			less++;
			ft_less_child(child, tmp2, less);
		}
		tmp2 = tmp2->next;
	}
}
