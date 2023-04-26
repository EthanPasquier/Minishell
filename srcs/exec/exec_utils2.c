/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 04:59:34 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 05:04:06 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_exit_last_cmd(t_token *token)
{
	t_token	*tmp;
	t_token	*last_cmd;

	tmp = token;
	last_cmd = NULL;
	while (tmp)
	{
		if (tmp->type == CMD)
			last_cmd = tmp;
		tmp = tmp->next;
	}
	if (last_cmd != NULL && !last_cmd->next)
	{
		if (ft_strcmp_caps((last_cmd->str), "exit", 4) == 0
			&& len(last_cmd) == 4)
			return (1);
	}
	return (0);
}

char	**ft_find_cmd(t_token *token)
{
	t_token	*tmp;
	char	**cmd;

	tmp = token;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE && tmp->type != CMD)
		tmp = tmp->next;
	if (tmp && tmp->type == CMD)
	{
		cmd = ft_split(tmp->str, ' ');
		if (cmd)
			return (cmd);
	}
	return (NULL);
}
