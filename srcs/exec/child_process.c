/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/01 12:25:10 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check which redirection 
void	ft_exec_child(t_child *child, t_token *token)
{
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	if ((token->next && token->next->type == PIPE
			&& (!token->prev || (token->prev->prev
					&& token->prev->prev->type != GREAT)))
		|| (token->prev && token->prev->type == PIPE))
		ft_child_pipe(child, token);
	if (((token->prev && token->prev->prev)
			&& (token->prev->prev->type == LESS
				|| token->prev->prev->type == GREAT)))
		ft_child_redirection_back(token, child);
	if (token->next
		&& (token->next->type == LESS || token->next->type == GREAT))
		ft_child_redirection_front(token, child);
	ft_close_fd(child->fd_array, child->cmd_nbr);
	// if (ft_is_builtin == 0)
		// ;
	// else
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
