/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:42:34 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/19 16:51:13 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_copy_env(char **env)
{
	char	**copy_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	copy_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (copy_env == NULL)
		return (NULL);
	j = 0;
	while (env[j])
	{
		copy_env[j] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1));
		if (copy_env[j] == NULL)
			return (NULL);
		ft_strlcpy(copy_env[j], env[j], ft_strlen(env[j]) + 1);
		j++;
	}
	copy_env[j] = NULL;
	return (copy_env);
}

t_token	*new_node(char *str)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->type = -1;
	new_node->str = ft_strdup(str);
	return (new_node);
}

int	ft_is_only_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != 32)
			return (1);
		i++;
	}
	return (0);
}
