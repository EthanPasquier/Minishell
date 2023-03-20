/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-Parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 10:33:19 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_fill_list(char **token)
{
	t_token *tokentype;
	t_token *tmp;
	int		i;

	i = 0;
	tokentype = NULL;
	tokentype = new_node(token[i++]);
	tmp = tokentype;
	while (token[i])
	{
		tmp->next = new_node(token[i]);
		if (!tmp->next)
		{
			ft_free_list(tokentype);
			ft_error(1);
		}
		tmp = tmp->next;
		i++;
	}
	return (tokentype);
}

void	ft_assign_type(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->str, "<<", 2) == 0)
			temp->type = LESS_LESS;
		else if (ft_strncmp(temp->str, ">>", 2) == 0)
			temp->type = GREAT_GREAT;
		else if (ft_strncmp(temp->str, "<", 1) == 0)
			temp->type = LESS;
		else if (ft_strncmp(temp->str, ">", 1) == 0)
			temp->type = GREAT;
		else if (ft_strncmp(temp->str, "-", 1) == 0)
			temp->type = ARG;
		else if (ft_strncmp(temp->str, "|", 1) == 0)
			temp->type = PIPE;
		else
			temp->type = CMD;
		temp = temp->next;
	}
}

void	ft_parser(t_init *var, t_token *tokentype)
{
	char	**pipe;
	char	**cmd;
	char	**all_path;
	char	*cmd_path;
	int i;

	all_path = find_path(var->envp);
	i = 0;
	pipe = ft_split(var->input, '|');
	while (pipe[i])
	{
		cmd = ft_split(pipe[i], ' ');
		cmd_path = find_cmd_path(cmd, all_path);
		execve(cmd_path, cmd, var->envp);
		// ft_free_double(cmd);
		// free(cmd_path);
		i++;
	}
	
	// for (int i = 0; cmd[i]; i++)
	// 	printf("%s\n", cmd[i]);
	tokentype = NULL;
	// token = ft_split(var->input, ' ');
	// tokentype = ft_fill_list(token);
	// ft_free_double(token);
	// ft_assign_type(tokentype);

	// return (tokentype);
}

