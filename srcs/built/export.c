/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:40:25 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/11 16:56:33 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		export[i] = ft_strdup(child->init->envp[i]);
		if (!export[i++])
			return (NULL);
	}
	while (child->cmd[j])
	{
		export[i] = ft_strdup(child->cmd[j++]);
		if (!export[i++])
			return (NULL);
	}
	export[i] = NULL;
	return (export);
}

void	sort_env_alph(char **env_copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strncmp(env_copy[i], env_copy[j], 255) > 0)
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
			j++;
		}
	}
}

void	ft_env_alph_order(char **env)
{
    int		i;
    int		count;
    char	**copy;

	count = 0;
	i = -1;
    while (env[count])
        count++;
    copy = malloc((count + 1) * sizeof(char *));
	while (++i < count)
		copy[i] = env[i];
    copy[count] = NULL;
	sort_env_alph(copy, count);
	i = -1;
	while (++i < count)
		printf("declare -x %s\n", copy[i]);
	free(copy);
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
	printf("%s\n", "TEST");
	if (!child->cmd[1])
		ft_env_alph_order(child->init->envp);
	else if (child->cmd[1])
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