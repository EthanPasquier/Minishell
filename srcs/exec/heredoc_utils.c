/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:06:13 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/12 11:05:28 by jalevesq         ###   ########.fr       */
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
	if (child->cmd_path)
		free(child->cmd_path);
	if (child->pipe_nbr > 0)
		ft_close_fd(child->fd_array, child->pipe_nbr);
	if (child->fd_array)
		free(child->fd_array);
	ft_free_list(token);
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