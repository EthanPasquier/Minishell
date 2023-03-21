/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:14:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/21 10:48:20 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Do error Function
static void	ft_exec_child(t_cmd *container, t_init *var, t_token *tmp_cmd)
{
	if (ft_is_prev_pipe(tmp_cmd) == 1)
	{
		if(dup2(container->pipefd[0], STDIN) == -1)
			ft_error(1); // temp, bad exit
		// fprintf(stderr, "%s\n", "pipefd0 stdin");
	}
	if (ft_is_next_pipe(tmp_cmd) == 1)
	{
		if(dup2(container->pipefd[1], STDOUT) == -1)
			ft_error(1); // temp, bad exit
		// fprintf(stderr, "%s\n", "pipefd1 stdout");
	}
	close(container->pipefd[0]);
	close(container->pipefd[1]);
	// fprintf(stderr, "%s\n", "Test");
	execve(container->cmd_path, container->cmd, var->envp);
	printf("execve error wtf\n");
	exit(EXIT_SUCCESS); // Change this end.
}

void	ft_child(t_cmd *container, t_init *var, t_token *tmp_cmd)
{
	int pid;
	pid = fork();
	if (pid == -1)
		ft_error(1); // Temp exit, very bad exit
	else if (pid == 0)
		ft_exec_child(container, var, tmp_cmd);
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	printf("%s\n", "Test");
}

t_token	*ft_next_cmd(t_token *token, t_cmd *container)
{
	t_token *tmp_cmd;
	int i;

	i = 0;
	tmp_cmd = token;
	if (tmp_cmd->type == CMD)
		i++;
	while (i <= container->i && tmp_cmd)
	{
		tmp_cmd = tmp_cmd->next;
		if (tmp_cmd->type == CMD)
			i++;
	}
	return (tmp_cmd);
}

void	ft_executor(t_cmd *container, t_init *var, t_token *token)
{
	t_token *tmp_cmd;

	tmp_cmd = ft_next_cmd(token, container);
	ft_child(container, var, tmp_cmd);
}

