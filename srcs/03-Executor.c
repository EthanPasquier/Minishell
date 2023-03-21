/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:14:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/21 18:34:49 by jalevesq         ###   ########.fr       */
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
	if (container->cmd_nbr > 1 && container->i < container->cmd_nbr - 1)
	{
		if(dup2(container->pipefd[1], STDOUT) == -1)
			ft_error(1); // temp, bad exit
		fprintf(stderr, "%s\n", "pipefd1 stdout");
	}
	close(container->pipefd[0]);
	close(container->pipefd[1]);
	// fprintf(stderr, "%s\n", "Test");
	execve(container->cmd_path, container->cmd, var->envp);
	// printf("execve error wtf\n");
	exit(EXIT_SUCCESS); // Change this end.
}

void	ft_child(t_cmd *container, t_init *var)
{

	container->pid = fork();
	if (container->pid == -1)
		ft_error(1); // Temp exit, very bad exit
	else if (container->pid == 0)
		ft_exec_child(container, var);
	// printf("Right before waitpid\n");
	waitpid(container->pid, NULL, 0);

}

// t_token	*ft_next_cmd(t_token *token, t_cmd *container)
// {
// 	t_token *tmp_cmd;
// 	int i;

// 	i = 0;
// 	tmp_cmd = token;
// 	if (tmp_cmd->type == CMD)
// 		i++;
// 	while (i <= container->i && tmp_cmd)
// 	{
// 		tmp_cmd = tmp_cmd->next;
// 		if (tmp_cmd->type == CMD)
// 			i++;
// 	}
// 	return (tmp_cmd);
// }

void	ft_executor(t_cmd *container, t_init *var)
{
	container->cmd_nbr = 0;

	while (container->pipe_split[container->cmd_nbr])
		container->cmd_nbr++;
	// exit(EXIT_SUCCESS);
	ft_child(container, var);
	// printf("%s\n", "coucou");
}

