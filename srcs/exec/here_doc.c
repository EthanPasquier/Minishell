/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:23:23 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/10 20:01:17 by jalevesq         ###   ########.fr       */
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

void	ft_do_heredoc(t_token *token, t_child *child, int i)
{
	while (1)
	{
		child->heredoc.str = readline(">");
		if (ft_strncmp(child->heredoc.str, token->next->str, ft_strlen(token->next->str)) == 0
			&& ft_strlen(token->next->str) == ft_strlen(child->heredoc.str))
			break ;
		if (child->heredoc.flag_doc == 1
			&& i == child->heredoc.here_doc_nbr - 1)
		{
			write(child->heredoc.here_docfd[1],
				child->heredoc.str, ft_strlen(child->heredoc.str));
			write(child->heredoc.here_docfd[1], "\n", 1);
		}
	}
	exit(EXIT_SUCCESS);
}

int	ft_is_doc_last(t_token *token)
{
	t_token	*tmp;
	int		type;

	tmp = token;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	type = -1;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == LESS || tmp->type == LESS_LESS)
			type = tmp->type;
		tmp = tmp->next;
	}
	if (type == LESS_LESS)
		return (1);
	return (0);
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
		while (i < child->heredoc.here_doc_nbr)
		{
			while (tmp->type != LESS_LESS)
				tmp = tmp->next;
			pid[i] = fork();
			if (pid[i] < 0)
			{
				write(2, "pid error in here doc\n", 22);
				return ;
			}
			if (pid[i] == 0)
				ft_do_heredoc(tmp, child, i);
			waitpid(pid[i], NULL, 0);
			tmp = tmp->next;
			i++;
		}
		free(pid);
	}
}
