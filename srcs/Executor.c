/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:39:17 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/29 09:28:38 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exec_command(t_token *t, t_child *c, int *fd, int *pid)
{
	t_token	*tmp;

	tmp = t;
	while (tmp && tmp->type != CMD)
		tmp = tmp->next;
	while (c->i < c->cmd_nbr)
	{
		if (tmp->type == CMD)
		{
			c->cmd = ft_split(tmp->str, ' ');
			c->cmd_path = find_cmd_path(c->cmd, c->all_path);
			if (c->cmd_path != NULL)
				ft_process_child(c, tmp, fd, pid);
			else
				printf("minishell: %s: command not found\n", c->cmd[0]);
			ft_free_exec(c->cmd, c->cmd_path);
		}
		c->i++;
		while (tmp->next && tmp->next->type != CMD)
			tmp = tmp->next;
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}

void	ft_command(t_token *token, t_child *child)
{
	int		*fd_array;
	pid_t	*pid;

	fd_array = NULL;
	pid = malloc(sizeof(pid_t) * child->cmd_nbr);
	if (!pid)
	{
		printf("PID ERROR wtf\n");
		exit(EXIT_FAILURE);
	}
	if (child->cmd_nbr > 1)
		fd_array = ft_set_pipe(child);
	ft_exec_command(token, child, fd_array, pid);
	if (child->cmd_nbr > 1)
		ft_close_child(fd_array, child->cmd_nbr);
	ft_wait(pid, child->cmd_nbr);
	if (fd_array != NULL)
		free(fd_array);
	free(pid);
}

void	ft_executor(t_token *token, char **envp)
{
	t_child	child;

	child.cmd_nbr = cmd_counter(token);
	child.all_path = find_path(envp);
	child.envp = envp;
	child.i = 0;
	ft_command(token, &child);
	ft_free_double(child.all_path);
}
