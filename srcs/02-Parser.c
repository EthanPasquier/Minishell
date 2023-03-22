/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-Parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/21 18:51:10 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// Error func good ?
t_token	*ft_fill_list(char **token)
{
	t_token *tokentype;
	t_token *tmp;
	int		i;

	i = 0;
	tokentype = NULL;
	tokentype = new_node(token[i++]);
	tokentype->prev = NULL;
	tmp = tokentype;
	while (token[i])
	{
		tmp->next = new_node(token[i++]);
		if (!tmp->next)
			ft_end_list(tokentype);
		tmp->next->prev = tmp;
		tmp = tmp->next;
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
		else if (ft_strncmp(temp->str, "|", 1) == 0)
			temp->type = PIPE;
		else
			temp->type = CMD;
		temp = temp->next;
	}
}

t_token *ft_exec_fill(t_token *token, t_init *var)
{
	char **split_token = ft_split(var->input, ' ');
	token = ft_fill_list(split_token);
	if (!token)
	{
		printf("Error in fill list token");
		exit(EXIT_FAILURE);
	}
	ft_free_double(split_token);
	ft_assign_type(token);

	return (token);
}

void	ft_parser(t_init *var)
{
	t_cmd container;
	// t_token *token;
	if (pipe(container.pipefd) == -1)
		ft_error(1); // temp, bad exit.
	// token = NULL;
	container.i = 0;
	container.all_path = find_path(var->envp); // Split PATH= Variable in ENVP
	container.pipe_split = ft_split(var->input, '|'); // Split input at each pipe
	while (container.pipe_split[container.i]) // While there is command.
	{
		container.cmd = ft_split(container.pipe_split[container.i], ' '); // Split the command at each space so cat -e is: cat, -e.
		container.cmd_path = find_cmd_path(container.cmd, container.all_path); // Try to find the path to the command in the ENV variable.
		if (!container.cmd_path)
		{
			error_cmd_path(&container);
			return ;
		}
		// token = ft_exec_fill(token, var); // Fill a linked with the input split at each space and type assign to it.
		ft_executor(&container, var); // try to execute the command find in cmd_path.
		// ft_free_list(token);
		free_cmd(&container);
		container.i++;
	}
	free_container(&container);
}

	// token = ft_split(var->input, ' ');
	// tokentype = ft_fill_list(token);
	// ft_free_double(token);
	// ft_assign_type(tokentype);

	// return (tokentype);