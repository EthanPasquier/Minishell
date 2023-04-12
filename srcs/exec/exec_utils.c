/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:14:23 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/12 18:09:11 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*ft_set_pipe(t_child *child)
{
	int	*fd_array;
	int	pipe_fd[2];
	int	fd_index;
	int	index_cmd;

	index_cmd = 0;
	fd_index = 0;
	fd_array = malloc(sizeof(int *) * (child->pipe_nbr) * 2);
	if (!fd_array)
		return (NULL);
	while (index_cmd < child->pipe_nbr)
	{
		if (pipe(pipe_fd) == -1)
			write(2, "pipe error in set_pipe\n", 23);
		fd_array[fd_index] = pipe_fd[1];
		fd_array[fd_index + 1] = pipe_fd[0];
		fd_index += 2;
		index_cmd++;
	}
	return (fd_array);
}

void	ft_close_fd(int *fd_array, int pipe_nbr)
{
	int	i;
	int	index;

	index = 0;
	i = 0;
	if (pipe_nbr > 0)
	{
		while (index < pipe_nbr)
		{
			if (fd_array[i] > 0)
				close(fd_array[i]);
			if (fd_array[i + 1] > 0)
				close(fd_array[i + 1]);
			i += 2;
			index++;
		}
	}
}

int	cmd_counter(t_token *token)
{
	t_token	*tmp;
	int		cmd_nbr;

	tmp = token;
	cmd_nbr = 0;
	while (tmp)
	{
		if (tmp->type == CMD)
			cmd_nbr++;
		tmp = tmp->next;
	}
	return (cmd_nbr);
}

void	ft_wait(pid_t *pid, t_child *child)
{
	int	i;
	int status;

	i = 0;
	while (i < child->pipe_nbr + 1)
	{
		waitpid(pid[i], &status, 0);
		if (child->is_builtin != 2)
		{
			if (status == 0)
				child->exit_code = 0;
			else if (status / 256 == 5)
				child->exit_code = 127;
			else
				child->exit_code = 1;
		}
		i++;
	}
}

int	ft_is_cmd(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
