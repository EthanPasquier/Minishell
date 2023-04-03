/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/03 16:38:26 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static void	ft_open_less(t_token *start, t_child *child, int *fd)
{
	int j;

	j = 0;
	while(j < child->less_mark && start)
	{
		if (start->type == LESS)
		{
			*fd = open(start->next->str, O_RDONLY);
			if (*fd == -1)
			{
				fprintf(stderr, "%s\n", start->next->str);
				ft_child_error(start, child, ERR_OPEN);
			}
			j++;
			if (j < child->less_mark)
				close(*fd);
		}
		start = start->next;
	}
}

void ft_less_child(t_child *child, t_token *token)
{
	t_token	*start;
	int		fd;

	start = token;
	fd = -1;
	if (child->less_mark > 0)
	{
		ft_open_less(start, child, &fd);
		if (dup2(fd, STDIN) == -1)
		{
			close(fd);
			ft_child_error(start, child, ERR_DUP2);
		}
		close(fd);
	}
}

