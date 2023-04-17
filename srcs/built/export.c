/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:40:25 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/17 19:15:09 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Faire une struct t_export
static char	**copy_exist(t_child *child, int line, int export_nbr, int *i)
{
	char	**export;

	export = (char **)ft_calloc((line + export_nbr + 1), sizeof(char *));
	if (!export)
		return (NULL);
	while (*i < line)
	{
		export[*i] = ft_strdup(child->init->envp[*i]);
		if (!export[*i])
			return (NULL);
		*i += 1;
	}
	return (export);
}

static char	*ft_dup_export(char **export, t_child *c, int *i, int j)
{
	export[*i] = ft_strdup(c->cmd[j]);
	if (!export[*i])
		return (NULL);
	*i += 1;
	return (export[*i]);
}

static char	**ft_add(int line, int export_nbr, t_child *child)
{
	char	**export;
	int		exist;
	int		i;
	int		j;

	j = 0;
	i = 0;
	export = copy_exist(child, line, export_nbr, &i);
	while (child->cmd[++j])
	{
		exist = ft_does_it_exist(i, j, export, child);
		if (ft_check_if_29(child->cmd[j]) == 0
			&& ft_digit_equal(child->cmd[j]) == 0)
		{
			if (exist >= 0)
			{
				free(export[exist]);
				export[exist] = ft_strdup(child->cmd[j]);
			}
			else
				export[i] = ft_dup_export(export, child, &i, j);
		}
	}
	export[i] = NULL;
	return (export);
}

static void	ft_env_alph_order(char **env)
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
	char	**export;

	line = 0;
	if (!child->cmd[1])
		ft_env_alph_order(child->init->envp);
	else if (child->cmd[1])
	{
		export_nbr = ft_export_nbr(child);
		if (child->cmd_nbr == 1)
		{
			while (child->init->envp[line])
				line++;
			export = ft_add(line, export_nbr, child);
			ft_free_double(child->init->envp);
			child->init->envp = export;
		}
	}
	return (0);
}
