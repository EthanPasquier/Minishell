/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:49:12 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/06 14:24:49 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_builtins(t_token *token)
{
	t_token *tmp;

	tmp = token;

	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	while ((tmp && tmp->type != CMD) && (tmp && tmp->type != PIPE))
		tmp = tmp->next;
	if (tmp && tmp->type == CMD)
	{
		if (ft_strcmp_caps((tmp->str), "pwd", 3) == 0)
			return (1);
		else if (ft_strcmp_caps((tmp->str), "env", 3) == 0)
			return (2);
		else if (ft_strcmp_caps((tmp->str), "unset", 5) == 0)
			return (3);
		else if (ft_strcmp_caps((tmp->str), "export", 6) == 0)
			return (4);
		else if (ft_strcmp_caps((tmp->str), "cd", 2) == 0)
			return (5);
		else if (ft_strcmp_caps((tmp->str), "exit", 4) == 0)
			return (6);
		else if (ft_strcmp_caps((tmp->str), "echo", 4) == 0)
			return (7);
	}
	return (-1);
}

void	ft_which_builtins(t_child *child)
{
	if (child->is_builtin == 1)
		ft_pwd();
	else if (child->is_builtin == 2)
		ft_env(child);
	// else if (child->is_builtin == 3)
	// 	ft_unset(child);
	// else if (child->is_builtin == 4)
	// 	ft_export(child);
	// else if (child->is_builtin == 5)
	// 	ft_cd(child);
	// else if (child->is_builtin == 6)
	// 	ft_exit(child);
	// else if (child->is_builtin == 7)
	// 	ft_echo(child);
	ft_free_double(child->cmd);
	exit(EXIT_SUCCESS);
}