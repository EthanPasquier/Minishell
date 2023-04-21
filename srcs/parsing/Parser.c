/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:33:54 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/21 16:37:10 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_commandoption(char *str)
{
	char	*new;
	int		i;

	i = 6;
	new = ft_strnstr(str, "echo ", 6);
	if (new != NULL)
	{
		while (str[i] == 32)
			i++;
		if (str[i - 1] != '-')
			return (str);
		new = ft_echoargument(str, 0);
		if (ft_strncmp(new, str, ft_strlen(str)) != 0)
			free(str);
		return (new);
	}
	else
	{
		new = ft_strnstr(str, "export ", 8);
		if (new != NULL)
			return (ft_exportsyntax(str));
	}
	return (str);
}

void	ft_setupnode(t_token *tmp)
{
	int	result;

	result = ft_syntax(tmp->str);
	tmp->str[1] = 0;
	ft_insertnode(tmp, result, 1);
}

void	ft_parser_suite(char *str, t_token *tmp, t_child *child)
{
	char	*test;

	while (tmp)
	{
		str = ft_strtrim(tmp->str, " ");
		if (ft_syntax(str) == 1 || ft_ordreguillemet(str) == 1)
		{
			free(str);
			child->exit_code = 1;
			return ;
		}
		free(tmp->str);
		test = ft_strdup(str);
		tmp->str = ft_guillemet(str, child, 0);
		if (str && tmp->str && ft_strncmp(tmp->str, test, ft_strlen(test)) == 0)
			free(str);
		free(test);
		str = ft_strtrim(tmp->str, " ");
		free(tmp->str);
		tmp->str = ft_commandoption(str);
		if (ft_syntax(tmp->str) >= 2)
			ft_setupnode(tmp);
		tmp = tmp->next;
	}
	child->exit_code = 0;
}

void	ft_parser(t_child *child)
{
	char	*str;
	char	**split;
	t_token	*token;
	t_token	*tmp;

	str = ft_strtrim(child->init->input, " ");
	if (ft_wake_word(str[0]) == 1 || ft_wake_word(str[ft_strlen(str) - 1]) > 0)
	{
		child->exit_code = ft_error_syntax(str);
		free(str);
		return ;
	}
	str[ft_strlen(str)] = 0;
	split = ft_write_cut(str);
	free(str);
	token = ft_fill_list(split);
	ft_free_double(split);
	tmp = token;
	ft_parser_suite(str, tmp, child);
	if (child->exit_code == 1)
		return (ft_free_list(token));
	ft_assign_type(token);
	ft_executor(token, child);
	if (token)
		ft_free_list(token);
}
