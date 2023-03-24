/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09-Utils_Exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:14:23 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/24 13:47:41 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*ft_set_pipe(t_cmd *container)
{
	int	*fd_array;
	int	pipe_fd[2];
	int	fd_index;
	int index_cmd;
	
	index_cmd = 0;
	fd_index = 0;
	fd_array = malloc(sizeof(int *) * (container->cmd_nbr - 1) * 2);
	if (!fd_array)
		ft_error(1); // à Changer
	while (index_cmd < container->cmd_nbr)
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

void ft_close_child(int *fd_array, int cmd_nbr)
{
	int i;

	i = 0;
	while (i < (cmd_nbr - 1) * 2)
		close(fd_array[i++]);
}