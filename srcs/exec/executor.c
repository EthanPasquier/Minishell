/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:39:17 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/04 14:36:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_command(t_token *t, t_child *c, pid_t *pid)
{
	t_token	*tmp;

	tmp = t;
	while (tmp)
	{
		if (c->i == 0 || tmp->type == PIPE)
		{
			ft_process_child(c, tmp, pid);
			c->i++;
		}
		tmp = tmp->next;
	}
}

void	ft_command(t_token *token, t_child *child)
{
	pid_t	*pid;

	child->fd_array = NULL;
	// +1 because ls | cat == 2 child process.
	pid = (pid_t *)malloc(sizeof(pid_t) * (child->pipe_nbr + 1));
	if (!pid)
	{
		fprintf(stderr, "PID ERROR\n");
		exit(EXIT_FAILURE);
	}
	child->fd_array = ft_set_pipe(child);
	ft_exec_command(token, child, pid);
	if (child->pipe_nbr > 0)
		ft_close_fd(child->fd_array, child->pipe_nbr);
	ft_wait(pid, child->pipe_nbr + 1);
	if (child->fd_array != NULL)
		free(child->fd_array);
	free(pid);
}

int	ft_pipe_counter(t_token *token)
{
	t_token *tmp;
	int i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_executor(t_token *token, char **envp)
{
	t_child	child;

	child.pipe_nbr = ft_pipe_counter(token);
	child.cmd_nbr = cmd_counter(token);
	child.all_path = find_path(envp);
	child.envp = envp;
	child.i = 0;
	ft_command(token, &child);
	ft_free_double(child.all_path);
}
