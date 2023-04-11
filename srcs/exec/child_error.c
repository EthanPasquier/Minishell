/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:51:42 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/11 19:12:24 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_failed_command(void)
{
	fprintf(stderr, "\u26A0 Command failed to execute.\n");
	exit(EXIT_SUCCESS);
}

void	ft_fd_error(t_token *token, t_child *c, int flag)
{
	if (flag == ERR_OPEN)
	{
		fprintf(stderr, "%s: No such file or directory\n", token->next->str);
		if (c->pipe_nbr > 0)
			ft_close_fd(c->fd_array, c->cmd_nbr);
		exit(EXIT_SUCCESS);
	}
	else if (flag == ERR_DUP2)
	{
		fprintf(stderr, "\u26A0 Dup2 error at: %s.\n", token->next->str);
		if (c->pipe_nbr > 0)
			ft_close_fd(c->fd_array, c->cmd_nbr);
		exit(EXIT_SUCCESS);
	}
}

void	ft_child_error(t_token *token, t_child *c, int flag)
{
	if (flag == ERR_EXECVE)
		ft_failed_command();
	else if (flag == ERR_OPEN || flag == ERR_DUP2)
		ft_fd_error(token, c, flag);
	else if (flag == ERR_PID)
		;
}
