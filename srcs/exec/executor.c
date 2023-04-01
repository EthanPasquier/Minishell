/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:39:17 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/01 12:02:04 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_command(t_token *t, t_child *c, int *pid)
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
				ft_process_child(c, tmp, pid);
			else
				printf("\u274C Minishell: %s: command not found\n", c->cmd[0]);
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
	pid_t	*pid;

	child->fd_array = NULL;
	pid = malloc(sizeof(pid_t) * child->cmd_nbr);
	if (!pid)
	{
		fprintf(stderr, "PID ERROR\n");
		exit(EXIT_FAILURE);
	}
	if (child->cmd_nbr > 1)
		child->fd_array = ft_set_pipe(child);
	ft_exec_command(token, child, pid);
	if (child->cmd_nbr > 1)
		ft_close_fd(child->fd_array, child->cmd_nbr);
	ft_wait(pid, child->cmd_nbr);
	if (child->fd_array != NULL)
		free(child->fd_array);
	free(pid);
}

void ft_redirection_no_cmd(t_token *token)
{
	t_token *tmp;
	int fd2;
	int flag;

	tmp = token;
	while (tmp && (tmp->type == LESS || tmp->type == GREAT))
	{
		flag = -1;
		fd2 = -1;
		if (tmp->type == LESS)
			ft_type_less(tmp, &flag, &fd2);
		else if (tmp->type == GREAT)
			ft_type_great(tmp, &flag, &fd2);
		if (flag != -1)
			return ;
		tmp = ft_next_redir(tmp);
	}
}

void	ft_executor(t_token *token, char **envp)
{
	t_child	child;

	child.cmd_nbr = cmd_counter(token);
	child.all_path = find_path(envp);
	child.envp = envp;
	child.i = 0;
	if (child.cmd_nbr <= 0
		&& (token->type == GREAT || token->type == LESS))
		ft_redirection_no_cmd(token);
	else
		ft_command(token, &child);
	ft_free_double(child.all_path);
}
