/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Child_Process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/29 09:54:10 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_child_redirection(t_token *token)
{
	if (token->next && token->next->type == GREAT)
		ft_child_great(token);
	if (token->prev && token->prev->type == LESS)
		;
}

void	ft_exec_child(t_child *child, t_token *token, int *fd)
{
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	if ((token->next && token->next->type == GREAT)
		|| (token->prev && token->prev->type == LESS))
		ft_child_redirection(token);
	if ((token->next && token->next->type == PIPE)
		|| (token->prev && token->prev->type == PIPE))
		ft_child_pipe(child, token, fd);
	if (child->cmd_nbr > 1)
		ft_close_child(fd, child->cmd_nbr);
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
