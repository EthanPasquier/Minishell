/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:42:34 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/16 12:05:11 by epasquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_init	ft_init(char *input)
{
	t_init var;

	var.input = input;
	return (var);
}

t_token *new_node(char *str)
{
	t_token *new_node;
	int i;
	
	i = 0;
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->type = -1;
	new_node->str = ft_strdup(str); // !!! Free les str dans les struct ET free le ft_split.

	return (new_node);
}