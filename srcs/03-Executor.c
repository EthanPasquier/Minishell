/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:14:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/24 14:09:11 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Do error Function

void	single_command(t_cmd *container, char **envp)
{
	container->cmd = ft_split(container->pipe_split[0], ' ');
	container->pid = fork();
	if (container->pid <= -1)
		ft_error(1); // Temp exit, very bad exit
	else if (container->pid == 0)
	{
		execve(container->cmd_path, container->cmd, envp);
		printf("Error, single command execve failed"); // change this end
	}
	waitpid(container->pid, NULL, 0);
}

void	ft_exec_child(t_cmd *container, int i, char **envp, int *fd_array)
{
	int	j;

	j = i * 2; // j = pipfd[1] et j+1 = pipfd[0]
	container->cmd = ft_split(container->pipe_split[i], ' ');
	if (i == 0)
	{
		if (dup2(fd_array[j], STDOUT) == -1)
			ft_error(1); // temp, bad exit
	}
	else if (i == container->cmd_nbr - 1)
	{
		if (dup2(fd_array[j - 1], STDIN) == -1)
			ft_error(1); // temp, bad exit
	}
	else
	{
		if (dup2(fd_array[j - 1], STDIN) == -1)
			ft_error(1); // temp, bad exit
		if (dup2(fd_array[j], STDOUT) == -1)
			ft_error(1); // temp, bad exit//
	}
	ft_close_child(fd_array, container->cmd_nbr);
	execve(container->all_cmd_path[i], container->cmd, envp);
	ft_error(1);
}

void ft_child(t_cmd *container, char **envp, int *fd_array)
{
	pid_t	*pid;
	int		i;

	i = 0;
	pid = malloc(sizeof(pid_t) * container->cmd_nbr);
	if (!pid)
		ft_error(1);
	while (i < container->cmd_nbr)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			ft_error(1);
		else if (pid[i] == 0)
			ft_exec_child(container, i, envp, fd_array); // first segfault
		i++;
	}
	ft_close_child(fd_array, container->cmd_nbr);
	i = 0;
	while (i < container->cmd_nbr)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
}

void	multiple_command(t_cmd *container, char **envp)
{
	int		*fd_array;

	fd_array = ft_set_pipe(container);
	ft_child(container, envp, fd_array);
	free(fd_array);
}

void	ft_executor(t_cmd *container, char **envp)
{
	// Check < > hereif true change fd to outfile/ infile in CHILD process.How ?
	if (container->cmd_nbr <= 1)
		single_command(container, envp);
	else
		multiple_command(container, envp);
}

// ls
// cat MAKEFILE
// wc

// void	ft_child(t_cmd *container, char **envp)
// {
// 	if (container->i == 0)
// 	{
// 		if (pipe(container->pipefd) == -1)
// 			ft_error(1);
// 	}
// 	container->pid = fork();
// 	if (container->pid <= -1)
// 		ft_error(1); // Temp exit, very bad exit
// 	else if (container->pid == 0)
// 		ft_exec_child(container, envp);
// 	close(container->pipefd[1]);
// 	waitpid(container->pid, NULL, 0);
// }

// static void	ft_exec_child(t_cmd *container, char **envp)
// {
// 	if ((container->i + 1) % 2 == 0 && container->i != 0)
// 	{
// 		if(dup2(container->pipefd[0], STDIN) == -1)
// 			ft_error(1); // temp, bad exit
// 		fprintf(stderr, "%s\n", "pipefd0 stdin");
// 	}
// 	close(container->pipefd[0]);
// 	if ((container->i + 1) % 2 != 0 && container->i < container->cmd_nbr - 1)
// 	{
// 		if(dup2(container->pipefd[1], STDOUT) == -1)
// 			ft_error(1); // temp, bad exit
// 		fprintf(stderr, "%s\n", "pipefd1 stdout");
// 	}
// 	close(container->pipefd[1]);
// 	fprintf(stderr, "%s\n", "EXECVE");
// 	execve(container->cmd_path, container->cmd, envp);
// 	// printf("execve error wtf\n");
// 	exit(EXIT_SUCCESS); // Change this end.
// }