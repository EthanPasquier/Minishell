/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/30 19:26:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check which redirection 
void	ft_exec_child(t_child *child, t_token *token, int *fd)
{
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	if ((token->next && token->next->type == LESS)
		|| (token->prev && token->prev->prev
		&& token->prev->prev->type == LESS))
		{
			fprintf(stderr, "LESS\n");
			ft_child_less_redirections(token);
			// token = token->next->next;
			// while (token->next && token->next->type == LESS && token->next->next)
			// 	token = token->next->next;
				
		}
	if ((token->next && token->next->type == GREAT)
		|| (token->prev && token->prev->type == FILE
		&& token->prev->prev && token->prev->prev->type == GREAT))
		{
			fprintf(stderr, "GREAT\n");
			ft_child_great_redirection(token);
			// token = token->next->next;
			// while (token->next && token->next->type == GREAT && token->next->next)
			// 	token = token->next->next;
		}

	if ((token->next && token->next->type == PIPE
		&& (!token->prev || (token->prev->prev && token->prev->prev->type != GREAT)))
		|| (token->prev && token->prev->type == PIPE))
		{
			fprintf(stderr, "PIPE\n");
			ft_child_pipe(child, token, fd);
		}
	
	if (child->cmd_nbr > 1)
		ft_close_fd(fd, child->cmd_nbr);
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
