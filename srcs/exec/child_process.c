/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/03 17:02:26 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static void	ft_redirection(t_token *token, t_child *child)
{
	t_token	*tmp;

	tmp = token;
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	while (tmp && tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	child->great_mark = ft_mark_count(tmp, GREAT);
	child->less_mark = ft_mark_count(tmp, LESS);
	ft_less_child(child, tmp);
	ft_great_child(child, tmp);
	ft_pipe_child(child, token);
}

static void	ft_exec_child(t_child *child, t_token *token)
{
	ft_redirection(token, child);
	ft_close_fd(child->fd_array, child->pipe_nbr);
	// if (ft_is_builtin == 0)
		// ;
	// else
	if (ft_is_cmd(token) == 1)
	{
		execve(child->cmd_path, child->cmd, child->envp);
		ft_child_error(token, child, ERR_EXECVE);
	}
}

void	ft_process_child(t_child *c, t_token *tmp, pid_t *pid)
{
	pid[c->i] = fork();
	if (pid[c->i] < 0)
		ft_error(1);
	else if (pid[c->i] == 0)
		ft_exec_child(c, tmp); // Change FD for | and < >.
}
