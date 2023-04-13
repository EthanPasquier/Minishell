/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:51:42 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/13 09:04:50 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_free_child(t_token *token, t_child *c)
{
	if (c->heredoc.flag_doc == 1)
	{
		close(c->heredoc.here_docfd[0]);
		close(c->heredoc.here_docfd[1]);
	}
	if (c->all_path)
		ft_free_double(c->all_path);
	if (c->cmd)
		ft_free_double(c->cmd);
	if (c->cmd_path && c->is_builtin < 0)
		free(c->cmd_path);
	if (c->pipe_nbr > 0)
		ft_close_fd(c->fd_array, c->pipe_nbr);
	if (c->fd_array)
		free(c->fd_array);
	ft_free_double(c->init->envp);
	while (token && token->prev)
		token = token->prev;
	ft_free_list(token);
	free(c->init->input);
	free(c->init);
	free(c);
}

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
		ft_free_child(token, c);
		exit(4);
	}
	else if (flag == ERR_DUP2)
	{
		fprintf(stderr, "\u26A0 Dup2 error at: %s.\n", token->next->str);
		ft_free_child(token, c);
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
