/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:01:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/05 15:37:48 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_less_n_great(t_child *child, t_token *tmp)
{
	t_token *tmp2;
	int		great;
	int		less;

	tmp2 = tmp;
	great = 0;
	less = 0;
	while (tmp2 && tmp2->type != PIPE)
	{
		if (tmp2->type == GREAT || tmp2->type == GREAT_GREAT)
		{
			great++;
			ft_great_child(child, tmp2, great);
		}
		else if (tmp2->type == LESS)
		{
			less++;	
			ft_less_child(child, tmp2, less);
		}
		tmp2 = tmp2->next;
	}
}

static void	ft_redirection(t_token *tmp, t_child *child)
{
	child->j = child->i * 2; // j = pipfd[1] et j+1 = pipfd[0]
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
			ft_error(1);
		}
		close(child->heredoc.here_docfd[0]);
		close(child->heredoc.here_docfd[1]);
	}
	ft_pipe_child(child, tmp);
}

static void	ft_exec_child(t_child *child, t_token *token)
{
	t_token *tmp;

	tmp = token;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	ft_redirection(tmp, child);
	ft_close_fd(child->fd_array, child->pipe_nbr);
	if (ft_is_cmd(token) == 1)
	{
		while (tmp->type != CMD)
			tmp = tmp->next;
		child->cmd = ft_split(tmp->str, ' ');
		child->cmd_path = find_cmd_path(child->cmd, child->all_path);
		if (!child->cmd_path)
		{
			fprintf(stderr,"\u274C Minishell: %s: command not found\n", child->cmd[0]);
			ft_free_double(child->cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			execve(child->cmd_path, child->cmd, child->envp);
			ft_child_error(token, child, ERR_EXECVE);
		}
	}
	else
		exit(EXIT_SUCCESS);
}

void	ft_process_child(t_child *c, t_token *tmp, pid_t *pid)
{
	pid[c->i] = fork();
	if (pid[c->i] < 0)
		ft_error(1);
	else if (pid[c->i] == 0)
		ft_exec_child(c, tmp); // Change FD for | and < >.
}
