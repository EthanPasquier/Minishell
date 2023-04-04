/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/04 13:34:40 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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