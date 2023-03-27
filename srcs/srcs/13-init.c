/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:42:34 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/27 10:56:45 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_init	ft_init(char *input, char **envp)
{
	t_init var;

	var.input = input;
	var.envp = envp;
	return (var);
}

t_token *new_node(char *str)
{
	t_token *new_node;
	
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->type = -1;
	new_node->str = ft_strdup(str); // !!! Free les str dans les struct ET free le ft_split.

	return (new_node);
}