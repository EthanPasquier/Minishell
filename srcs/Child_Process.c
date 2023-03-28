/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Child_Process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/28 18:30:12 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function is for >
void	ft_great(int *fd2, t_token *tmp)
{
	while (tmp && tmp->type == GREAT)
	{
		*fd2 = -1;
		*fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
		if (tmp->next && tmp->next->next && tmp->next->type == FILE
			&& tmp->next->next->type == GREAT)
		{
			close(*fd2);
			tmp = tmp->next->next;
		}
		else
			break ;
	}	
}

void	ft_child_redirection(t_token *t)
{
	int		fd2;
	t_token	*tmp;

	tmp = t;
	fd2 = -1;
	if (t->next && t->next->type == GREAT)
	{
		tmp = tmp->next;
		if (tmp->next->next && tmp->next->next->type == GREAT)
			ft_great(&fd2, tmp);
		else
			fd2 = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
		if (dup2(fd2, STDOUT) == -1)
			ft_error(1); // temp, bad exit
		close(fd2);
		// fprintf(stderr, "fd2, STDOUT\n");
	}
}

void	ft_child_pipe(t_child *c, t_token *t, int *fd)
{
	if (t->prev && t->prev->type == PIPE && t->next && t->next->type == PIPE)
	{
		if (dup2(fd[c->j - 1], STDIN) == -1)
			ft_error(1); // temp, bad exit
		if (dup2(fd[c->j], STDOUT) == -1)
			ft_error(1); // temp, bad exit//
		// fprintf(stderr, "ELSE - fd[%d - 1], STDIN\n", c->j);
		// fprintf(stderr, "ELSE - fd[%d], STDOUT\n", c->j);
	}
	else if (c->i == 0 && t->next && t->next->type == PIPE)
	{
		if (dup2(fd[c->j], STDOUT) == -1)
			ft_error(1); // temp, bad exit
		// fprintf(stderr, "fd[%d], STDOUT\n", c->j);
	}
	else if (t->prev && t->prev->type == PIPE)
	{
		if (dup2(fd[c->j - 1], STDIN) == -1)
			ft_error(1); // temp, bad exit
		// fprintf(stderr, "fd[%d - 1], STDIN\n", c->j);
	}
}

void	ft_exec_child(t_child *child, t_token *token, int *fd)
{
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	if (token->next && token->next->type == GREAT)
		ft_child_redirection(token);
	if ((token->next && token->next->type == PIPE)
		|| (token->prev && token->prev->type == PIPE))
		ft_child_pipe(child, token, fd);
	ft_close_child(fd, child->cmd_nbr);
	execve(child->cmd_path, child->cmd, child->envp);
	ft_error(1);
}

void	ft_process_child(t_child *c, t_token *tmp, int *fd, int *pid)
{
	c->cmd = ft_split(tmp->str, ' ');
	c->cmd_path = find_cmd_path(c->cmd, c->all_path);
	if (c->cmd_path != NULL)
	{
		pid[c->i] = fork();
		if (pid[c->i] < 0)
			ft_error(1);
		else if (pid[c->i] == 0)
			ft_exec_child(c, tmp, fd); // Change FD for | and < >.
	}
}
