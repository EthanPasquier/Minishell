/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:14:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 13:21:48 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_child(t_cmd *container, t_init *var)
{
	if (container->i - 1 >= 0)
	{
		if(dup2(container->pipefd[0], STDIN) == -1)
			ft_error(1); // temp, bad exit
		fprintf(stderr, "%s\n", "pipefd0 stdin");
	}
	if (container->pipe_split[container->i + 1])
	{
		if(dup2(container->pipefd[1], STDOUT) == -1)
			ft_error(1); // temp, bad exit
		fprintf(stderr, "%s\n", "pipefd1 stdout");
	}
	close(container->pipefd[0]);
	close(container->pipefd[1]);
	execve(container->cmd_path, container->cmd, var->envp);
	printf("execve error wtf\n");
	exit(EXIT_SUCCESS); // Change this end.
}

void	ft_executor(t_cmd *container, t_init *var)
{
	int pid;

	if (pipe(container->pipefd) == -1)
		ft_error(1); // temp, bad exit.
	pid = fork();
	if (pid == -1)
		ft_error(1); // Temp exit, very bad exit
	else if (pid == 0)
		ft_child(container, var);
	close(container->pipefd[0]);
	close(container->pipefd[1]);
	waitpid(pid, NULL, 0);
	
	// write(1, "\n", 1);
}
