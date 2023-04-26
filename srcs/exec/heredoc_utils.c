/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:06:13 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 05:34:04 by jalevesq         ###   ########.fr       */
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
	free(child->trash_path);
	free(child->init->input);
	free(child->init);
	free(child);
	clear_history();
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

void	ft_sig_n_input(t_child *child)
{
	// int	i;
	
	// i = 0;
	signal(SIGINT, ft_quit);
	child->heredoc.str = readline(">");
	// while (child->heredoc.str[i])
	// {
	// 	if (child->heredoc.str[i] == '$' && child->heredoc.str[i+1]
	// 		&& ft_strchr(" $", child->heredoc.str[i+1] != NULL))
	// 		break;
	// 	i++;
	// }
	// if (i < ft_strlen(child->heredoc.str))
	// 	ft_env_var_heredoc(child);
	
}

// void	ft_env_var_heredoc(t_child *child)
// {
// 	int		i;
// 	int		new_char_nbr;
// 	char	*env_var;
// 	char	*new_str;

// 	i = 0;
// 	new_char_nbr = 0;
	
	
// }