/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/02 11:06:52 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

	// if ((token->next && token->next->type == PIPE
	// 		&& (!token->prev || (token->prev->prev
	// 				&& token->prev->prev->type != GREAT)))
	// 	|| (token->prev && token->prev->type == PIPE))
	// 	ft_child_pipe(child, token);
	// if (((token->prev && token->prev->prev)
	// 		&& (token->prev->prev->type == LESS
	// 			|| token->prev->prev->type == GREAT)))
	// 	ft_child_redirection_back(token, child);
	// if (token->next
	// 	&& (token->next->type == LESS || token->next->type == GREAT))
	// 	ft_child_redirection_front(token, child);
	// ft_close_fd(child->fd_array, child->cmd_nbr);
	// // if (ft_is_builtin == 0)
	// 	// ;
	// // else

int	ft_mark_count(t_token *token, int type)
{
	t_token *tmp;
	int i;

	i = 0;
	tmp = token;
	while(tmp && tmp->type != PIPE)
	{
		if (tmp->type == type)
			i += 1;
		tmp = tmp->next;
	}
	return (i);
}

// Check which redirection 
void	ft_exec_child(t_child *child, t_token *token)
{
	t_token	*tmp;
	t_token *start;
	t_token	*start2;

	int		j;
	int		fd;

	tmp = token;
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	///////////////////
	while(tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	child->great_mark = ft_mark_count(tmp, GREAT);
	child->less_mark = ft_mark_count(tmp, LESS);
	///////////////////
	start = tmp;
	start2 = tmp;
	j = 0;
	if (child->less_mark > 0)
	{
		while(j < child->less_mark && start2)
		{
			if (start2->type == LESS)
			{
				fd = open(start2->next->str, O_RDONLY);
				if (fd == -1)
					ft_child_error(start2, child, ERR_OPEN);
				j++;
				if (j < child->less_mark)
				{
					close(fd);
				}
			}
			start2 = start2->next;
		}
		if (dup2(fd, STDIN) == -1)
		{
			close(fd);
			ft_child_error(start2, child, ERR_DUP2);
		}
		close(fd);
	}
	///////////////////
	j = 0;
	fd = -1;
	if (child->great_mark > 0)
	{
		while (j < child->great_mark && start)
		{
			if (start->type == GREAT)
			{
				fd = open(start->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
				if (fd == -1)
				{
					ft_child_error(start, child, ERR_OPEN);
					exit(EXIT_SUCCESS);
				}
				j++;
				if (j < child->great_mark)
				{
					close(fd);
				}
			}
			start = start->next;
		}
		if (dup2(fd, STDOUT) == -1)
		{
			close(fd);
			ft_child_error(start, child, ERR_DUP2);
		}
		close(fd);
	}
	fd = -1;
	///////////////////
	// void ft_is_pipe
	if (child->great_mark == 0 && ft_is_next_pipe(token) == 1)
	{
		if (dup2(child->fd_array[child->j], STDOUT) == -1)
			ft_child_error(token, child, ERR_DUP2);
	}
	if (child->less_mark == 0 && ft_is_prev_pipe(token) == 1)
	{
		if (dup2(child->fd_array[child->j - 1], STDIN) == -1)
			ft_child_error(token, child, ERR_DUP2);
	}
	// fprintf(stderr, "%s\n", start->next->str);
	// exit(EXIT_FAILURE);
	// if (ft_is_builtin == 0)
		// ;
	// else
	ft_close_fd(child->fd_array, child->cmd_nbr);
	execve(child->cmd_path, child->cmd, child->envp);
	ft_child_error(token, child, ERR_EXECVE);
}

void	ft_process_child(t_child *c, t_token *tmp, int *pid)
{
	pid[c->i] = fork();
	if (pid[c->i] < 0)
		return ;
	else if (pid[c->i] == 0)
		ft_exec_child(c, tmp); // Change FD for | and < >.
}
