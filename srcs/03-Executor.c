/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:14:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/23 10:39:38 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Do error Function
static void	ft_exec_child(t_cmd *container, char **envp)
{
	if (container->i > 0 && container->i < container->cmd_nbr)
	{
		if(dup2(container->pipefd[0], STDIN) == -1)
			ft_error(1); // temp, bad exit
	}
	close(container->pipefd[0]);
	if (container->cmd_nbr > 1 && container->i < container->cmd_nbr - 1)
	{
		if(dup2(container->pipefd[1], STDOUT) == -1)
			ft_error(1); // temp, bad exit
	}
	close(container->pipefd[1]);
	execve(container->cmd_path, container->cmd, envp);
	printf("execve error wtf\n");
	exit(EXIT_SUCCESS); // Change this end.
}


void	single_command(t_cmd *container, char **envp)
{
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

void	multiple_command(t_cmd *container, char **envp)
{
	if (container->flag_pipe == 0)
	{
		if(pipe(container->pipefd) == -1)
			ft_error(1);
		container->flag_pipe = 1;
	}

	container->pid = fork();
	if (container->pid <= -1)
		ft_error(1); // Temp exit, very bad exit
	else if (container->pid == 0)
		ft_exec_child(container, envp);
	if (container->flag_pipe == 1)
		close(container->pipefd[1]);
	waitpid(container->pid, NULL, 0);
}

void	ft_child(t_cmd *container, char **envp)
{
	container->pid = fork();
	if (container->pid <= -1)
		ft_error(1); // Temp exit, very bad exit
	else if (container->pid == 0)
		ft_exec_child(container, envp);
	close(container->pipefd[1]);
	waitpid(container->pid, NULL, 0);
}

void	ft_executor(t_cmd *container, char **envp)
{
	// Check < > here, if true, change fd to outfile/infile in CHILD process. How?
	if (container->cmd_nbr <= 1)
		single_command(container, envp);
	else if (container->cmd_nbr == 2)
		ft_child(container, envp);
	else
		multiple_command(container, envp);
}


