/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:49:12 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 04:58:25 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp->str[i] && tmp->str[i] != ' ')
		i++;
	return (i);
}

int	ft_is_builtins(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	while ((tmp && tmp->type != CMD) && (tmp && tmp->type != PIPE))
		tmp = tmp->next;
	if (tmp && tmp->str && tmp->type == CMD)
	{
		if (ft_strcmp_caps((tmp->str), "unset", 5) == 0 && len(tmp) == 5)
			return (1);
		else if (ft_strcmp_caps((tmp->str), "cd", 2) == 0 && len(tmp) == 2)
			return (2);
		else if (ft_strcmp_caps((tmp->str), "exit", 4) == 0 && len(tmp) == 4)
			return (3);
		else if (ft_strcmp_caps((tmp->str), "export", 6) == 0 && len(tmp) == 6)
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

void	ft_which_builtins(t_child *child, t_token *token, pid_t *pid)
{
	int	error;

	error = 0;
	if (child->is_builtin == 1)
		error = ft_unset(child);
	else if (child->is_builtin == 2)
		error = ft_cd(child);
	else if (child->is_builtin == 3)
		ft_exit(child, token, pid);
	else if (child->is_builtin == 4)
		error = ft_export(child);
	child->exit_code = error;
}

void	ft_which_builtins_child(t_child *child, t_token *token)
{
	int	exit_code;

	if (child->is_builtin == 3)
		ft_exit(child, token, NULL);
	else if (child->is_builtin == 4 && !child->cmd[1])
		ft_export(child);
	else if (child->is_builtin == 5)
		ft_pwd();
	else if (child->is_builtin == 6)
		ft_env(child);
	else if (child->is_builtin == 7)
		ft_echo(child);
	if (child->is_builtin == 3)
	{
		exit_code = child->exit_code;
		ft_free_child(token, child);
		exit(exit_code);
	}
	else
	{
		ft_free_child(token, child);
		exit(EXIT_SUCCESS);
	}
}

char	*ft_getenv(char **envp, char *var)
{
	char	*find;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			find = ft_strtrim(envp[i], var);
			return (find);
		}
		i++;
	}
	return (NULL);
}
