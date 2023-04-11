/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:40:25 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/10 20:14:22 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_add(int line, int export_nbr, t_child *child)
{
	char	**export;
	int		i;
	int		j;

	j = 1;
	i = 0;
	export = (char **)ft_calloc((line + export_nbr + 1), sizeof(char *));
	if (!export)
		return (NULL);
	while (i < line)
	{
		export[i] = (char *)malloc(sizeof(char) * (ft_strlen(child->init->envp[i]) + 1));
		if (!export[i])
			return (NULL);
		ft_strlcpy(export[i], child->init->envp[i], ft_strlen(child->init->envp[i]) + 1);
		if (!export[i])
			return (NULL);
		i++;
	}
	while (child->cmd[j])
	{
		export[i] = (char *)malloc(sizeof(char) * (ft_strlen(child->cmd[j]) + 1));
		if (!export[i])
			return (NULL);
		ft_strlcpy(export[i], child->cmd[j], ft_strlen(child->cmd[j]) + 1);
		if (!export[i])
			return (NULL);
		i++;
		j++;
	}
	export[i] = NULL;
	return (export);
}

int	ft_export(t_child *child)
{
	int		export_nbr;
	int		line;
	int		j;
	char	**export;
	
	export_nbr = 0;
	line = 0;
	j = 1;
	if (child->cmd[1])
	{
		while (child->init->envp[line])
			line++;
		while (child->cmd[j])
		{
			j++;
			export_nbr++;
		}
		export = ft_add(line, export_nbr, child);
		ft_free_double(child->init->envp);
		child->init->envp = export;
	}
	return (0);
}