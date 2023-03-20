/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:14:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 11:09:58 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_child(t_cmd *container, t_init *var)
{
	execve(container->cmd_path, container->cmd, var->envp);
}

void	ft_executor(t_cmd *container, t_init *var)
{
	int pid;

	pid = fork();
	if (pid == -1)
		ft_error(1); // Temp exit, very bad exit
	else if (pid == 0)
		ft_child(container, var);
	waitpid(pid, NULL, 0);
	// write(1, "\n", 1);
}
