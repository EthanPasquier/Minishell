/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:39:17 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/27 20:49:31 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exec_single(t_child *child, char **envp, char *str)
{
	pid_t	pid;

	pid = fork();
	child->cmd = ft_split(str, ' ');
	child->cmd_path = find_cmd_path(child->cmd, child->all_path);
	if (child->cmd_path == NULL)
		printf("minishell: %s: command not found", child->cmd[0]);
	if (pid < 0)
		ft_error(1); // Free list (and return ?)
	if (pid == 0)
	{
		execve(child->cmd_path, child->cmd, envp);
		printf("Execve Single command Failed\n");
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	ft_free_exec(child->cmd, child->cmd_path);
}

void ft_child_pipe(t_child *c, t_token *t, int *fd)
{
	(void)t;
	if (c->i == 0)
	{
		if (dup2(fd[c->j], STDOUT) == -1)
			ft_error(1); // temp, bad exit
	}
	else if (c->i == c->cmd_nbr - 1)
	{
		if (dup2(fd[c->j - 1], STDIN) == -1)
			ft_error(1); // temp, bad exit
	}
	else
	{
		if (dup2(fd[c->j - 1], STDIN) == -1)
			ft_error(1); // temp, bad exit
		if (dup2(fd[c->j], STDOUT) == -1)
			ft_error(1); // temp, bad exit//
	}
}

// void	ft_child_redirection(t_child *child, t_token *token, int *fd)
// {
// 	if (token->next && token->next->type == GREAT)
// 	{
		
// 	}
// }

void	ft_exec_child(t_child *child, t_token *token, int *fd)
{
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	if ((token->next && token->next->type == PIPE)
		|| (token->prev && token->prev->type == PIPE))
		ft_child_pipe(child, token, fd);
	// if (token->next && token->next->type == GREAT)
	// 	ft_child_redirection(child, token, fd);
	ft_close_child(fd, child->cmd_nbr);
	execve(child->cmd_path, child->cmd, child->envp);
	ft_error(1);
}

void	ft_exec_multiple(t_token *t, t_child *c, int *fd, int *pid)
{
	t_token	*tmp;

	tmp = t;
	while (tmp && tmp->type != CMD)
		tmp = tmp->next;
	while (c->i < c->cmd_nbr)
	{
		c->cmd = ft_split(tmp->str, ' ');
		c->cmd_path = find_cmd_path(c->cmd, c->all_path);
		if (c->cmd_path == NULL)
			printf("minishell: %s: command not found\n", c->cmd[0]);
		else
		{
			pid[c->i] = fork();
			if (pid[c->i] < 0)
				ft_error(1);
			else if (pid[c->i] == 0)
				ft_exec_child(c, tmp, fd); // Change FD for | and < >.
		}
		c->i++;
		ft_free_exec(c->cmd, c->cmd_path);
		while (tmp->next && tmp->next->type != CMD && c->i < c->cmd_nbr)
			tmp = tmp->next;
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}

void	ft_multiple_command(t_token *token, t_child *child)
{
	int		*fd_array;
	pid_t	*pid;

	child->i = 0;
	pid = malloc(sizeof(pid_t) * child->cmd_nbr);
	if (!pid)
	{
		printf("PID ERROR wtf\n");
		exit(EXIT_FAILURE);
	}
	fd_array = ft_set_pipe(child);
	ft_exec_multiple(token, child, fd_array, pid);
	ft_close_child(fd_array, child->cmd_nbr);
	ft_wait(pid, child->cmd_nbr);
	free(pid);
	free(fd_array);
}

void	ft_executor(t_token *token, char **envp)
{
	t_child	child;

	child.cmd_nbr = cmd_counter(token);
	child.all_path = find_path(envp);
	child.envp = envp;
	if (is_one_command(token) == 0)
		ft_exec_single(&child, envp, token->str);
	else
		ft_multiple_command(token, &child);
	ft_free_double(child.all_path);
}
