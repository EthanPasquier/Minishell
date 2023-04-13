/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:40:25 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/13 16:44:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_check_if_29(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 29)
			return (1);
		i++;
	}
	return (0);
}

int	ft_digit_equal(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) == 1)
			return (1);
		i++;
	}
	if (str[i] && str[i] == '=')
		return (0);
	return(1);
}

int	ft_does_it_exist(int i, int j, char **export, t_child *child)
{
	int n;

	n = 0;
	while (n < i)
	{
		if (ft_strncmp(export[n], child->cmd[j], len_equal(child->cmd[j])) == 0)
			return (n);	
		n++;
	}
	return (-1);
}

char	**ft_add(int line, int export_nbr, t_child *child)
{
	char	**export;
	int		i;
	int		j;
	int		exist;

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
			{
				export[i] = ft_strdup(child->cmd[j]);
				if (!export[i])
					return (NULL);
				i++;
			}
		}
		j++;
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
	if (!child->cmd[1])
		ft_env_alph_order(child->init->envp);
	else if (child->cmd[1])
	{
		while (child->init->envp[line])
			line++;
		while (child->cmd[j])
		{
			if (ft_check_if_29(child->cmd[j]) == 0
				&& ft_digit_equal(child->cmd[j]) == 0)
				export_nbr++;
			else
			{
				write(2, "minishell: export: ", 19);
				write(2, child->cmd[j], ft_strlen(child->cmd[j]));
				write(2, ": not a valid identifier\n", 25);
			}
			j++;
		}
		export = ft_add(line, export_nbr, child);
		ft_free_double(child->init->envp);
		child->init->envp = export;
	}
	return (0);
}