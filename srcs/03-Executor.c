/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04-Executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:14:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/16 14:35:07 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	ft_cmd_nbr(t_token *token)
// {
// 	t_token *tmp;
// 	int i;

// 	i = 0;
// 	tmp = token;
// 	while (tmp)
// 	{
// 		if (tmp->type == CMD)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// t_token	*ft_find_node(t_token *token, int cmd_index)
// {
// 	t_token *tmp;
// 	int i;

// 	i = 1;
// 	tmp = token;
// 	while(tmp)
// 	{
// 		if (tmp->type == CMD && cmd_index == i)
// 			return (tmp);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }

// void	ft_command(t_init *var, t_token *token)
// {
// 	int		cmd_nbr;
// 	int		i;

// 	i = 1;
// 	cmd_nbr = ft_cmd_nbr(token);
// 	while (i <= cmd_nbr)
// 	{
// 		cmd_node = ft_find_node(token, i);
		
// 	}
// }