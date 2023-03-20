/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-Parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 13:22:43 by jalevesq         ###   ########.fr       */
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

void	ft_parser(t_init *var)
{
	t_cmd container;

	container.i = 0;
	container.all_path = find_path(var->envp);
	container.pipe_split = ft_split(var->input, '|');
	while (container.pipe_split[container.i])
	{
		container.cmd = ft_split(container.pipe_split[container.i], ' ');
		container.cmd_path = find_cmd_path(container.cmd, container.all_path);
		if (!container.cmd_path)
		{
			printf("minishell: %s: command not found.\n", container.cmd[0]); // Exit en même temps
			exit(EXIT_SUCCESS);
		}
		ft_executor(&container, var);
		ft_free_double(container.cmd);
		free(container.cmd_path);
		container.i++;
	}
	free_container(&container);
}


	// token = ft_split(var->input, ' ');
	// tokentype = ft_fill_list(token);
	// ft_free_double(token);
	// ft_assign_type(tokentype);

	// return (tokentype);