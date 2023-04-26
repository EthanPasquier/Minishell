/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:39:17 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 05:57:20 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_pipe_counter(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/**
 * Main function of the executor that checks the here_docs,
 * checks if the command is a builtin and calls the function
 * that creates the childs process. 
 **/
static void	ft_exec_command(t_token *t, t_child *c, pid_t *pid)
{
	t_token	*tmp;

	tmp = t;
	while (tmp)
	{
		c->heredoc.here_doc_nbr = ft_heredoc_nbr(tmp);
		c->heredoc.flag_doc = ft_is_doc_last(tmp);
		if (c->i == 0 || tmp->type == PIPE)
		{
			c->is_builtin = ft_is_builtins(tmp);
			ft_heredoc(tmp, c, pid);
			ft_process_child(c, tmp, pid);
			if (c->heredoc.flag_doc == 1)
			{
				close(c->heredoc.here_docfd[1]);
				close(c->heredoc.here_docfd[0]);
			}
			c->i++;
		}
		tmp = tmp->next;
	}
}

/**
 * This function creates an array of pipes and malloc
 * pid_t the number of child processes there will be (1 per pipe + 1). 
**/
static void	ft_command(t_token *token, t_child *child)
{
	pid_t	*pid;

	child->fd_array = NULL;
	pid = (pid_t *)malloc(sizeof(pid_t) * (child->pipe_nbr + 1));
	if (!pid)
		return ;
	if (child->pipe_nbr > 0)
		child->fd_array = ft_set_pipe(child);
	if (child->fd_array == NULL && child->pipe_nbr > 0)
	{
		free(pid);
		return ;
	}
	ft_exec_command(token, child, pid);
	if (child->pipe_nbr > 0)
		ft_close_fd(child->fd_array, child->pipe_nbr);
	ft_wait(pid, child);
	free(pid);
	if (child->fd_array != NULL)
		free(child->fd_array);
}

void	ft_check_pwd(t_child *child)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		if (chdir(child->trash_path) == -1)
			return ;
	}
	else
		return ;
}

/**
 * The first function of the executor. It is used to initiate and call
 * one of the main functions, ft_command. After executing the command,
 * ft_check_pwd is called to check if the pwd is accessible. If it is not,
 * then the pwd is changed to the .Trash or the HOME variable in env.
**/
void	ft_executor(t_token *token, t_child *child)
{
	child->is_exit_last_cmd = ft_is_exit_last_cmd(token);
	child->pipe_nbr = ft_pipe_counter(token);
	child->cmd_nbr = cmd_counter(token);
	child->all_path = find_path(child);
	child->flag_cmd = -1;
	child->cmd_path = NULL;
	child->i = 0;
	ft_command(token, child);
	ft_check_pwd(child);
	ft_free_double(child->all_path);
}
