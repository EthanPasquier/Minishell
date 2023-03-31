/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/31 17:15:39 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_child_redirection_back(t_token *token)
{
	t_token *tmp;
	int fd2;
	int first_great;
	int first_less;

	tmp = token->prev;
	first_less = 0;
	first_less = 0;
	fd2 = -1;
	fprintf(stderr, "%s\n", tmp->str);
	while (tmp->prev && (tmp->prev->type == LESS || tmp->prev->type == GREAT))
	{
		fprintf(stderr, "TEST\n");
		if (tmp->prev->type == LESS)
		{
			fd2 = open(tmp->str, O_RDONLY);
			if (fd2 == -1)
			{
				perror(tmp->str);
				exit(EXIT_SUCCESS);
			}
			if (first_less == 0)
			{
				first_less = 1;
				if (dup2(fd2, STDIN) == -1)
					ft_error(1);
			}
		}
		else if (tmp->prev->type == GREAT)
		{
			fd2 = open(tmp->str, O_WRONLY | O_TRUNC | O_CREAT, 0640);
			if (fd2 == -1)
			{
				perror(tmp->str);
				exit(EXIT_SUCCESS);
			}
			if (first_great == 0)
			{
				first_great = 1;
				if (dup2(fd2, STDOUT) == -1)
					ft_error(1);
			}
		}
		close(fd2);
		if (tmp->prev && tmp->prev->prev && (tmp->prev->prev->type == GREAT || tmp->prev->prev->type == LESS))
			tmp = tmp->prev;
		tmp = tmp->prev;
	}
	close(fd2);
}

// Check which redirection 
void	ft_exec_child(t_child *child, t_token *token, int *fd)
{
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	if (((token->prev && token->prev->prev)
		&& (token->prev->prev->type == LESS || token->prev->prev->type == GREAT)))		
		ft_child_redirection_back(token);
	if (token->next
		&& (token->next->type == LESS || token->next->type == GREAT))
		ft_child_redirection_front(token);
	if ((token->next && token->next->type == PIPE
		&& (!token->prev || (token->prev->prev && token->prev->prev->type != GREAT)))
		|| (token->prev && token->prev->type == PIPE))
		{
			fprintf(stderr, "PIPE\n");
			ft_child_pipe(child, token, fd);
		}
	
	if (child->cmd_nbr > 1)
		ft_close_fd(fd, child->cmd_nbr);
	fprintf(stderr, "EXECVE\n");
	execve(child->cmd_path, child->cmd, child->envp);
	ft_error(1);
}

void	ft_process_child(t_child *c, t_token *tmp, int *fd, int *pid)
{
	pid[c->i] = fork();
	if (pid[c->i] < 0)
		ft_error(1);
	else if (pid[c->i] == 0)
		ft_exec_child(c, tmp, fd); // Change FD for | and < >.
}
