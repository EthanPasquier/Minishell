/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:23:23 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/14 14:38:33 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_do_heredoc(t_token *tmp, t_child *child, int i)
{
	while (1)
	{
		child->heredoc.str = readline(">");
		if (child->heredoc.str)
		{
			if (ft_strlen(child->heredoc.str) > 0)
			{
				if (ft_strncmp(child->heredoc.str, tmp->next->str,
						ft_strlen(tmp->next->str)) == 0
					&& ft_strlen(tmp->next->str)
					== ft_strlen(child->heredoc.str))
					break ;
				if (child->heredoc.flag_doc == 1
					&& i == child->heredoc.here_doc_nbr - 1)
				{
					write(child->heredoc.here_docfd[1],
						child->heredoc.str, ft_strlen(child->heredoc.str));
					write(child->heredoc.here_docfd[1], "\n", 1);
				}
			}
		}
		else
			ft_free_child_doc(child, tmp);
	}
	ft_free_child_doc(child, tmp);
}

static void	ft_do_child_doc(pid_t *p, int i, t_child *c, t_token *t)
{
	free(p);
	signal(SIGINT, ft_quit);
	ft_do_heredoc(t, c, i);
}

void	ft_doc_parent_process(pid_t *p, int i, t_child *c)
{
	int	status;

	waitpid(p[i], &status, 0);
	if (status / 256 == 3)
		c->exit_code = 1;
	else
		c->exit_code = 0;
}

void	ft_heredoc_child(t_child *c, pid_t *p, t_token *tmp, pid_t *p2)
{
	int	i;

	i = 0;
	while (i < c->heredoc.here_doc_nbr)
	{
		while (tmp->type != LESS_LESS)
			tmp = tmp->next;
		p[i] = fork();
		if (p[i] < 0)
			return ;
		if (p[i] == 0)
		{
			free(p2);
			ft_do_child_doc(p, i, c, tmp);
		}
		else if (p[i] > 0)
		{
			ft_doc_parent_process(p, i, c);
			tmp = tmp->next;
			i++;
		}
	}
}

void	ft_heredoc(t_token *token, t_child *child, pid_t *pid2)
{
	t_token	*tmp;
	pid_t	*pid;

	tmp = token;
	if (child->heredoc.here_doc_nbr > 0)
	{
		ft_pipe_doc(child);
		pid = malloc(sizeof(int) * child->heredoc.here_doc_nbr);
		if (!pid)
			return ;
		ft_heredoc_child(child, pid, tmp, pid2);
		free(pid);
	}
}
