/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/03 12:14:52 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_open_great(t_child *child, t_token *start, int *fd)
{
	int j;

	j = 0;
	while (j < child->great_mark && start)
		{
		if (start->type == GREAT)
		{
			*fd = open(start->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
			if (*fd == -1)
				ft_child_error(start, child, ERR_OPEN);
			j++;
			if (j < child->great_mark)
				close(*fd);
		}
		start = start->next;
	}
}

void	ft_great_child(t_child *child, t_token *token)
{
	t_token	*start;
	int		fd;

	start = token;
	fd = -1;
	if (child->great_mark > 0)
	{
		ft_open_great(child, start, &fd);
		if (dup2(fd, STDOUT) == -1)
		{
			close(fd);
			ft_child_error(start, child, ERR_DUP2);
		}
		close(fd);
	}
}