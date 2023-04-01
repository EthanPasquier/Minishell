/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/01 10:03:35 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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
