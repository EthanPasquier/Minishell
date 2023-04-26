/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:31:32 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 04:58:35 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_digit_in_msg(t_child *child, int *ft_exit)
{
	int	i;

	i = 0;
	if (child->cmd[1])
	{
		while (child->cmd[1][i])
		{
			if (ft_isdigit(child->cmd[1][i++]) == 0)
			{
				write(2, "minishell: exit: ", 17);
				write(2, child->cmd[1], ft_strlen(child->cmd[1]));
				write(2, ": numeric argument required\n", 28);
				return (1);
			}
		}
		if (child->cmd[2])
		{
			write(2, "minishell: exit: ", 17);
			write(2, ": Too many argument\n", 21);
			return (2);
		}
	}
	if (child->cmd[1])
		*ft_exit = ft_atoi(child->cmd[1]);
	return (0);
}

void	ft_free_exit(t_child *child, t_token *token)
{
	free(child->trash_path);
	ft_free_double(child->init->envp);
	ft_free_double(child->all_path);
	free(child->init->input);
	while (token && token->prev)
		token = token->prev;
	ft_free_list(token);
	rl_clear_history();
	ft_free_double(child->cmd);
	free(child->init);
	free(child);
}

void	ft_exit(t_child *child, t_token *token, pid_t *pid)
{
	int	flag;
	int	ft_exit;

	ft_exit = 0;
	flag = ft_digit_in_msg(child, &ft_exit);
	if (child->cmd_nbr == 1)
	{
		write(2, "exit\n", 5);
		free(pid);
		ft_free_exit(child, token);
		if (flag == 0)
			exit(ft_exit);
		else if (flag == 1)
			exit(255);
		else if (flag == 2)
			exit(1);
	}
	else if (flag == 0)
		child->exit_code = ft_atoi(child->cmd[1]);
	else if (flag == 1)
		child->exit_code = 255;
	else if (flag == 2)
		child->exit_code = 1;
}
