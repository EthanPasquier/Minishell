/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:14:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/22 09:36:30 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Do error Function
static void	ft_exec_child(t_cmd *container, t_init *var)
{
	if (container->i > 0 && container->i < container->cmd_nbr)
	{
		if(dup2(container->pipefd[0], STDIN) == -1)
			ft_error(1); // temp, bad exit
		fprintf(stderr, "%s\n", "pipefd0 stdin");
	}
	close(container->pipefd[0]);
	if (container->cmd_nbr > 1 && container->i < container->cmd_nbr - 1)
	{
		if(dup2(container->pipefd[1], STDOUT) == -1)
			ft_error(1); // temp, bad exit
		fprintf(stderr, "%s\n", "pipefd1 stdout");
	}
	close(container->pipefd[1]);
	// fprintf(stderr, "%s\n", get_next_line(container->pipefd[0]));
	fprintf(stderr, "%s\n", "EXECVE");
	execve(container->cmd_path, container->cmd, var->envp);
	printf("execve error wtf\n");
	exit(EXIT_SUCCESS); // Change this end.
}

void	ft_child(t_cmd *container, t_init *var)
{
	if (pipe(container->pipefd) == -1)
		ft_error(1); // temp, bad exit.
	container->pid = fork();
	if (container->pid <= -1)
		ft_error(1); // Temp exit, very bad exit
	else if (container->pid == 0)
		ft_exec_child(container, var);
	close(container->pipefd[0]);
	close(container->pipefd[1]);
	waitpid(container->pid, NULL, 0);
	printf("End of Child Process\n");
}

void	ft_executor(t_cmd *container, t_init *var)
{
	container->cmd_nbr = 0;

	while (container->pipe_split[container->cmd_nbr])
		container->cmd_nbr++;
	ft_child(container, var);
}

