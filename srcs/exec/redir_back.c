/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/01 14:05:28 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_open_back_less(int *first_less, t_token *tmp, t_child *c)
{
	int	fd2;

	fd2 = open(tmp->next->str, O_RDONLY);
	if (fd2 == -1)
		ft_child_error(tmp, c, ERR_OPEN);
	if (*first_less == 0)
	{
		*first_less = 1;
		if (dup2(fd2, STDIN) == -1)
		{
			close(fd2);
			ft_child_error(tmp, c, ERR_DUP2);
		}
	}
	return (fd2);
}

int	ft_open_back_great(int *first_great, t_token *tmp, t_child *c)
{
	int	fd2;

	fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (fd2 == -1)
		ft_child_error(tmp, c, ERR_OPEN);
	if (*first_great == 0)
	{
		*first_great = 1;
		if (dup2(fd2, STDOUT) == -1)
		{
			close(fd2);
			ft_child_error(tmp, c, ERR_DUP2);
		}
	}
	return (fd2);
}

void	ft_child_redirection_back(t_token *token, t_child *c)
{
	t_token	*tmp;
	int		fd2;
	int		first_great;
	int		first_less;

	tmp = token->prev->prev;
	first_less = 0;
	first_less = 0;
	fd2 = -1;
	while (tmp && (tmp->type == LESS || tmp->type == GREAT))
	{
		if (tmp->type == LESS)
			fd2 = ft_open_back_less(&first_less, tmp, c);
		else if (tmp->type == GREAT)
			fd2 = ft_open_back_great(&first_great, tmp, c);
		close(fd2);
		if (tmp->prev && tmp->prev->prev
			&& (tmp->prev->prev->type == GREAT
				|| tmp->prev->prev->type == LESS))
			tmp = tmp->prev;
		tmp = tmp->prev;
	}
	close(fd2);
}
