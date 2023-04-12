/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:31:32 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/12 13:06:27 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_child *child, t_token *token, pid_t *pid)
{
	ft_free_double(child->init->envp);
	ft_free_double(child->all_path);
	ft_free_double(child->cmd);
	free(pid);
	while (token && token->prev)
		token = token->prev;
	ft_free_list(token);
	free(child->init);
	free(child);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}