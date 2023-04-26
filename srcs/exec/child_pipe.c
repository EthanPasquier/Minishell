/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:42:54 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 05:01:09 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_is_next_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
		return (1);
	return (0);
}

static int	ft_is_prev_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->prev;
	if (tmp && tmp->type == PIPE)
		return (1);
	return (0);
}

void	ft_pipe_child(t_child *child, t_token *token)
{
	if (child->great_mark == 0 && ft_is_next_pipe(token) == 1)
	{
		if (dup2(child->fd_array[child->j], STDOUT) == -1)
			ft_child_error(token, child, ERR_DUP2);
	}
	if (child->less_mark == 0 && child->heredoc.flag_doc == 0
		&& ft_is_prev_pipe(token) == 1)
	{
		if (dup2(child->fd_array[child->j - 1], STDIN) == -1)
			ft_child_error(token, child, ERR_DUP2);
	}
}
