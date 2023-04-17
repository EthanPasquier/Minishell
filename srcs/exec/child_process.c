/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/17 19:16:08 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_redirection(t_token *tmp, t_child *child)
{
	child->j = child->i * 2;
	child->great_mark = ft_mark_count(tmp, GREAT);
	child->great_mark += ft_mark_count(tmp, GREAT_GREAT);
	child->less_mark = ft_mark_count(tmp, LESS);
	if (child->less_mark > 0 || child->great_mark > 0)
		ft_less_n_great(child, tmp);
	if (child->heredoc.flag_doc == 1)
	{
		if (dup2(child->heredoc.here_docfd[0], STDIN) == -1)
		{
			close(child->heredoc.here_docfd[0]);
			close(child->heredoc.here_docfd[1]);
			write(2, "Error dup2 here_doc\n", 22);
		}
		close(child->heredoc.here_docfd[0]);
		close(child->heredoc.here_docfd[1]);
	}
	ft_pipe_child(child, tmp);
}

static void	ft_exec_cmd(t_token *tmp, t_child *child)
{
	if ((child->is_builtin > 0 && child->is_builtin < 3)
		|| (child->is_builtin == 3 && !child->cmd[1]))
		return ;
	while (tmp->type != CMD)
		tmp = tmp->next;
	if (child->is_builtin > 3 || (child->is_builtin == 3 && child->cmd[1]))
		ft_which_builtins_child(child, tmp);
	else if (!child->cmd_path)
	{
		ft_cmd_error(child);
		ft_free_child(tmp, child);
		exit(5);
	}
	else if (child->cmd_path)
	{
		execve(child->cmd_path, child->cmd, child->init->envp);
		ft_child_error(tmp, child, ERR_EXECVE);
	}
}

static void	ft_exec_child(t_child *child, t_token *tmp)
{
	t_token	*tmp2;

	tmp2 = tmp;
	if (tmp2->type == PIPE)
		tmp2 = tmp2->next;
	ft_redirection(tmp2, child);
	if (child->pipe_nbr > 0)
		ft_close_fd(child->fd_array, child->pipe_nbr);
	if (ft_is_cmd(tmp) == 1)
		ft_exec_cmd(tmp2, child);
	ft_free_child(tmp2, child);
	exit(EXIT_SUCCESS);
}

static void	ft_builtins_or_cmd(t_child *c, t_token *tmp, pid_t *pid)
{
	if (c->is_builtin > 0 && c->is_builtin < 5)
	{
		if (c->cmd_nbr == 1 || c->is_builtin == 2
			|| c->is_builtin == 1 || c->is_builtin == 4)
		{
			if (c->is_builtin != 4 || (c->is_builtin == 4 && c->cmd[1]))
				ft_which_builtins(c, tmp, pid);
		}
	}
	else if (c->cmd && c->is_builtin < 0)
	{
		if (c->all_path || ft_strncmp(c->cmd[0], "/", 1) == 0)
			c->cmd_path = find_cmd_path(c);
	}
}

void	ft_process_child(t_child *c, t_token *tmp, pid_t *p)
{
	c->cmd = ft_find_cmd(tmp);
	ft_builtins_or_cmd(c, tmp, p);
	p[c->i] = fork();
	if (p[c->i] < 0)
		return ;
	else if (p[c->i] == 0)
	{
		if (p)
			free(p);
		ft_exec_child(c, tmp);
		exit(EXIT_SUCCESS);
	}
	if (c->cmd && c->is_builtin < 0)
		free(c->cmd_path);
	c->cmd_path = NULL;
	if (c->cmd)
		ft_free_double(c->cmd);
}
