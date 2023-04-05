/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:39:17 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/05 15:31:32 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_heredoc_nbr(t_token *t)
{
	t_token *tmp;
	int		i;

	tmp = t;
	i = 0;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == LESS_LESS)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_is_doc_last(t_token *token)
{
	t_token *tmp;
	int type;

	tmp = token;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	type = -1;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == LESS || tmp->type == LESS_LESS)
			type = tmp->type;
		tmp = tmp->next;
	}
	if (type == LESS_LESS)
		return (1);
	return (0);
}

void	ft_do_heredoc(t_token *token, t_child *child, int i)
{
	while (1)
	{
		child->heredoc.str = readline(">");
		if (ft_strncmp(child->heredoc.str, token->next->str, ft_strlen(token->next->str)) == 0
		&& ft_strlen(token->next->str) == ft_strlen(child->heredoc.str))
		break;
		if (child->heredoc.flag_doc == 1 && i == child->heredoc.here_doc_nbr - 1)
		{
			write(child->heredoc.here_docfd[1], child->heredoc.str, ft_strlen(child->heredoc.str));
			write(child->heredoc.here_docfd[1], "\n", 1);
		}
	}
	exit(EXIT_SUCCESS);
}


void	ft_heredoc(t_token *token, t_child *child)
{
	int		i;
	t_token *tmp;
	pid_t	*pid;

	i = 0;
	tmp = token;
	if (child->heredoc.here_doc_nbr > 0)
	{
		if (child->heredoc.flag_doc == 1)
		{
			if (pipe(child->heredoc.here_docfd) == -1)
				ft_error(1);
		}
		pid = malloc(sizeof(int) *  child->heredoc.here_doc_nbr);
		while (i < child->heredoc.here_doc_nbr)
		{
			while (tmp->type != LESS_LESS)
				tmp = tmp->next;
			pid[i] = fork();
			if (pid[i] < 0)
				ft_error(1);
			if (pid[i] == 0)
				ft_do_heredoc(tmp, child, i);
			waitpid(pid[i], NULL, 0);
			tmp = tmp->next;
			i++;
		}
		free(pid);
	}
}

void	ft_exec_command(t_token *t, t_child *c, pid_t *pid)
{
	t_token	*tmp;

	tmp = t;
	while (tmp)
	{
		c->heredoc.here_doc_nbr = ft_heredoc_nbr(tmp);
		c->heredoc.flag_doc = ft_is_doc_last(tmp);
		if (c->i == 0 || tmp->type == PIPE)
		{
			ft_heredoc(tmp, c);
			ft_process_child(c, tmp, pid);
			if (c->heredoc.flag_doc == 1)
			{
				close(c->heredoc.here_docfd[1]);
				close(c->heredoc.here_docfd[0]);
			}
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
