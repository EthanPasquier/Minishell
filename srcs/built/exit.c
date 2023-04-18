/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:31:32 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/18 15:07:30 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_digit_in_msg(t_child *child)
{
	int	i;

	i = 0;
	if (child->cmd[1])
	{
		while (child->cmd[1][i])
		{
			if (ft_isdigit(child->cmd[1][i]) == 0)
			{
				write(2, "minishell: exit: ", 17);
				write(2, child->cmd[1], ft_strlen(child->cmd[1]));
				write(2, ": numeric argument required\n", 28);
				break ;
			}
			i++;
		}
	}
}

void	ft_exit(t_child *child, t_token *token, pid_t *pid)
{
	ft_digit_in_msg(child);
	if (child->cmd_nbr == 1)
	{
		write(2, "exit\n", 5);
		free(child->trash_path);
		ft_free_double(child->init->envp);
		ft_free_double(child->all_path);
		free(child->init->input);
		free(pid);
		while (token && token->prev)
			token = token->prev;
		ft_free_list(token);
		clear_history();
		ft_free_double(child->cmd);
		free(child->init);
		free(child);
		exit(EXIT_SUCCESS);
	}
}
