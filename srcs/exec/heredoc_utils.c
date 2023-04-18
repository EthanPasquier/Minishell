/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:06:13 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/18 08:41:47 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_child_doc(t_child *child, t_token *token)
{
	if (child->heredoc.flag_doc == 1)
	{
		close(child->heredoc.here_docfd[0]);
		close(child->heredoc.here_docfd[1]);
	}
	ft_free_double(child->init->envp);
	if (child->all_path)
		ft_free_double(child->all_path);
	if (child->pipe_nbr > 0)
		ft_close_fd(child->fd_array, child->pipe_nbr);
	if (child->fd_array)
		free(child->fd_array);
	while (token && token->prev)
		token = token->prev;
	ft_free_list(token);
	clear_history();
	free(child->init->input);
	free(child->init);
	free(child);
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

void	ft_pipe_doc(t_child *child)
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
