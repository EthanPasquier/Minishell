/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/03 20:30:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_less_child(t_child *child, t_token *token, int less)
{
	t_token	*start;
	int		fd;

	start = token;
	fd = open(start->next->str, O_RDONLY);
		if (fd == -1)
			ft_child_error(start, child, ERR_OPEN);
	if (less == child->less_mark)
	{
		if (dup2(fd, STDIN) == -1)
		{
			close(fd);
			ft_child_error(start, child, ERR_DUP2);
		}
	}
	close(fd);
}

