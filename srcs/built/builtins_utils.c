/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:49:12 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/09 15:47:39 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	len(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp->str[i] && tmp->str[i] != ' ')
		i++;
	// fprintf(stderr, "%s\n", tmp->str);
	// fprintf(stderr, "%d\n", i);
	return (i);
}

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
		if (ft_strcmp_caps((tmp->str), "unset", 5) == 0 && len(tmp) == 5)
		{
			// fprintf(stderr, "TEST\n");
			return (1);
		}
		else if (ft_strcmp_caps((tmp->str), "export", 6) == 0 && len(tmp) == 6)
			return (2);
		else if (ft_strcmp_caps((tmp->str), "cd", 2) == 0 && len(tmp) == 2)
			return (3);
		else if (ft_strcmp_caps((tmp->str), "exit", 4) == 0 && len(tmp) == 4)
			return (4);
		if (ft_strcmp_caps((tmp->str), "pwd", 3) == 0 && len(tmp) == 3)
			return (5);
		else if (ft_strcmp_caps((tmp->str), "env", 3) == 0 && len(tmp) == 3)
			return (6);
		else if (ft_strcmp_caps((tmp->str), "echo", 4) == 0 && len(tmp) == 4)
			return (7);
	}
	return (-1);
}

void	ft_which_builtins(t_child *child, t_token *token)
{
	(void)token;
	(void)child;
	// if (child->is_builtin == 1)
	// 	ft_unset(child);
	// else if (child->is_builtin == 2)
	// 	ft_export(child);
	// else if (child->is_builtin == 3)
	// 	ft_cd(child);
	// else if (child->is_builtin == 4)
	// 	ft_exit(child);
}

void	ft_which_builtins_child(t_child *child)
{
	if (child->is_builtin == 5)
		ft_pwd();
	else if (child->is_builtin == 6)
		ft_env(child);
	// else if (child->is_builtin == 7)
	// 	ft_echo(child);
	exit(EXIT_SUCCESS);
}
