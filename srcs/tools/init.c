/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:42:34 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/06 09:30:18 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

 char **ft_copy_env(char **env)
 {
	char **copy_env;
	int i;
	int j;

	i = 0;
	while (env[i])
		i++;
	copy_env = (char **)malloc(sizeof(char*) * (i + 1));
	j = 0;
	while (env[j])
	{
		copy_env[j] = strdup(env[j]);
		j++;
	}
	copy_env[j] = NULL;
	// for (int i = 0; copy_env[i]; i++)
	// 		printf("%s\n", copy_env[i]);
	// exit(EXIT_FAILURE);
	return (copy_env);
 }

t_init	ft_init(char *input)
{
	t_init	var;

	var.input = input;
	return (var);
}

t_token	*new_node(char *str)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->type = -1;
	new_node->str = ft_strdup(str); // !!! Free les str dans les struct ET free le ft_split.
	return (new_node);
}