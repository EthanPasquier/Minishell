/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:26:15 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 11:00:34 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_free_double(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
	return (NULL);
}

void	ft_free_list(t_token *token)
{
	t_token *tmp;
	
	if (token)
	{
		while (token)
		{
			tmp = token->next;
			free(token->str); // free le strdup dans new_node
			free(token);
			token = tmp;
		}
	}
}

void	ft_error(int flag)
{
	if (flag == 1)
		printf("wtf");
	printf("ERROR help");
	exit(EXIT_SUCCESS);
}

void	free_container(t_cmd *container)
{
	ft_free_double(container->all_path);
	ft_free_double(container->pipe_split);
	// ft_free_double(container->cmd); // Both already free in while loop in ft_parser
	// free(container->cmd_path);
}