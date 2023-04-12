/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:23:23 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/12 09:07:32 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_heredoc_nbr(t_token *t)
{
	t_token	*tmp;
	int		i;

	tmp = t;
	i = 0;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == LESS_LESS)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_do_heredoc(t_token *token, t_token *tmp, t_child *child, int i)
{
	while (1)
	{
		child->heredoc.str = readline(">");
		if (ft_strncmp(child->heredoc.str, tmp->next->str, ft_strlen(tmp->next->str)) == 0
			&& ft_strlen(tmp->next->str) == ft_strlen(child->heredoc.str))
			break ;
		if (child->heredoc.flag_doc == 1
			&& i == child->heredoc.here_doc_nbr - 1)
		{
			write(child->heredoc.here_docfd[1],
				child->heredoc.str, ft_strlen(child->heredoc.str));
			write(child->heredoc.here_docfd[1], "\n", 1);
		}
	}
	ft_free_child_doc(child, token);
}

static void	ft_pipe_doc(t_child *child)
{
	if (child->heredoc.flag_doc == 1)
	{
		if (pipe(child->heredoc.here_docfd) == -1)
		{
			write(2, "Pipe here doc error\n", 20);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_heredoc_child(t_child *c, pid_t *p, t_token *t, t_token *tmp)
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
			free(p);
			ft_do_heredoc(t, tmp, c, i);
		}
		waitpid(p[i], NULL, 0);
		tmp = tmp->next;
		i++;
	}

}

void	ft_heredoc(t_token *token, t_child *child)
{
	int		i;
	t_token	*tmp;
	pid_t	*pid;

	i = 0;
	tmp = token;
	if (child->heredoc.here_doc_nbr > 0)
	{
		ft_pipe_doc(child);
		pid = malloc(sizeof(int) * child->heredoc.here_doc_nbr);
		if (!pid)
			return ;
		ft_heredoc_child(child, pid, token, tmp);
		free(pid);
	}
}
