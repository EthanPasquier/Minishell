/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:51:42 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/21 17:11:35 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_child(t_token *token, t_child *c)
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
	free(c->trash_path);
	ft_free_list(token);
	rl_clear_history();
	free(c->init->input);
	free(c->init);
	free(c);
}

void	ft_too_much_pipe(int *fd_array, int pipe_nbr)
{
	write(2, "Minishell: pipe: environment limit.", 35);
	write(2, " Use a better terminal or use less pipe.\n", 41);
	if (fd_array)
		ft_close_fd(fd_array, pipe_nbr);
	if (fd_array)
		free(fd_array);
}

static void	ft_fd_error(t_token *token, t_child *c, int flag)
{
	if (flag == ERR_OPEN_LESS)
	{
		write(2, token->next->str, ft_strlen(token->next->str));
		write(2, ": No such file or directory\n", 28);
		ft_free_child(token, c);
		exit(4);
	}
	else if (flag == ERR_OPEN_GREAT)
	{
		write(2, token->next->str, ft_strlen(token->next->str));
		write(2, ": Permission denied\n", 20);
		ft_free_child(token, c);
		exit(4);
	}
	else if (flag == ERR_DUP2)
	{
		write(2, "Dup2, error\n", 12);
		ft_free_child(token, c);
		exit(EXIT_SUCCESS);
	}
}

void	ft_child_error(t_token *token, t_child *c, int flag)
{
	if (flag == ERR_EXECVE)
	{
		write(2, "minishell: ", 11);
		write(2, c->cmd[0], ft_strlen(c->cmd[0]));
		write(2, ": command not found\n", 20);
		ft_free_child(token, c);
		exit(5);
	}
	else if (flag == ERR_OPEN_LESS || flag == ERR_OPEN_GREAT
		|| flag == ERR_DUP2)
		ft_fd_error(token, c, flag);
	else if (flag == ERR_PID)
		;
}

void	ft_exit_doc(t_token *token, t_child *child)
{
	ft_free_child_doc(child, token);
	exit(EXIT_SUCCESS);
}
