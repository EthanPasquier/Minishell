/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/11 19:20:23 by jalevesq         ###   ########.fr       */
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

static void	ft_exec_cmd(t_token *token, t_token *tmp, t_child *child)
{
	if ((child->is_builtin > 0 && child->is_builtin < 4))
		exit(EXIT_SUCCESS);
	while (tmp->type != CMD)
		tmp = tmp->next;
	if (child->is_builtin > 3
		|| (child->is_builtin == 4 && !child->cmd[1]))
			ft_which_builtins_child(child);
	else if (child->cmd_path)
	{
		execve(child->cmd_path, child->cmd, child->init->envp);
		ft_child_error(token, child, ERR_EXECVE);	
	}
}

static void	ft_exec_child(t_child *child, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	ft_redirection(tmp, child);
	if (child->pipe_nbr > 0)
		ft_close_fd(child->fd_array, child->pipe_nbr);
	free(child->fd_array);
	if (ft_is_cmd(token) == 1)
		ft_exec_cmd(token, tmp, child);
	exit(EXIT_SUCCESS);
}

static void	ft_builtins_or_cmd(t_child *c, t_token *tmp)
{
	if (c->is_builtin > 0 && c->is_builtin < 5)
	{
		if (c->cmd_nbr == 1)
		{
			if (c->is_builtin != 4 || (c->is_builtin == 4 && c->cmd[1]))
				ft_which_builtins(c, tmp);
		}
	}
	else if (c->cmd && c->all_path)
	{
		c->cmd_path = find_cmd_path(c->cmd, c->all_path);
		if (!c->cmd_path)
			ft_cmd_error(c);
		else
			c->exit_code = 0;
	}
}

void	ft_process_child(t_child *c, t_token *tmp, pid_t *pid)
{
	c->cmd = ft_find_cmd(tmp);
	ft_builtins_or_cmd(c, tmp);
	pid[c->i] = fork();
	if (pid[c->i] < 0)
		return ;
	else if (pid[c->i] == 0)
		ft_exec_child(c, tmp);
	ft_free_double(c->cmd);
	if (c->is_builtin < 0)
		free(c->cmd_path);
}
