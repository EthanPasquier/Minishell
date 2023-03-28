/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:14:23 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/28 11:11:50 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*ft_set_pipe(t_child *child)
{
	int	*fd_array;
	int	pipe_fd[2];
	int	fd_index;
	int	index_cmd;

	index_cmd = 0;
	fd_index = 0;
	fd_array = malloc(sizeof(int *) * (child->cmd_nbr - 1) * 2);
	if (!fd_array)
		ft_error(1); // à Changer
	while (index_cmd < child->cmd_nbr)
	{
		if (pipe(pipe_fd) == -1)
			ft_error(1);
		fd_array[fd_index] = pipe_fd[1];
		fd_array[fd_index + 1] = pipe_fd[0];
		fd_index += 2;
		index_cmd++;
	}
	return (fd_array);
}

void	ft_close_child(int *fd_array, int cmd_nbr)
{
	int	i;

	i = 0;
	while (i < (cmd_nbr - 1) * 2)
		close(fd_array[i++]);
}

int	is_one_command(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type != CMD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
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

void	ft_wait(pid_t *pid, int cmd_nbr)
{
	int	i;

	i = 0;
	while (i < cmd_nbr)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}
