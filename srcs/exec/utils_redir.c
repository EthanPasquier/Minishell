/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:09:11 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/31 11:11:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// go to next redir (Only use on no cmd)
t_token	*ft_next_redir(t_token *token)
{
	t_token *tmp;

	tmp = token;
	if (tmp->next && tmp->next->next 
			&& (tmp->next->next->type == GREAT
			|| tmp->next->next->type == LESS))
			tmp = tmp->next;
	tmp = tmp->next;
	return (tmp);
}


// Type less and no cmd
void ft_type_less(t_token *tmp, int *flag, int *fd2)
{
	*fd2 = open(tmp->next->str, O_RDONLY);
	if (*fd2 == -1)
	{
		perror(tmp->next->str);
		*flag = 1;
	}
	else
		close (*fd2);
}


// Type great and no cmd
void ft_type_great(t_token *tmp, int *flag, int *fd2)
{
	*fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (*fd2 == -1)
	{
		perror(tmp->next->str);
		*flag = 1;
	}
	else
		close(*fd2);
}

// Multiple Great front when cmd
void	ft_multiple_great_front(int *fd2, t_token *t)
{
	while (t && t->type == GREAT)
	{
		*fd2 = -1;
		*fd2 = open(t->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
		if (t->next && t->next->next && t->next->type == FILE
			&& t->next->next->type == GREAT)
		{
			close(*fd2);
			t = t->next->next;
		}
		else
			break ;
	}	
}