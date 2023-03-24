/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-Parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/24 09:13:34 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// Error func good ?
// t_token	*ft_fill_list(char **token)
// {
// 	t_token *tokentype;
// 	t_token *tmp;
// 	int		i;

// 	i = 0;
// 	tokentype = NULL;
// 	tokentype = new_node(token[i++]);
// 	tokentype->prev = NULL;
// 	tmp = tokentype;
// 	while (token[i])
// 	{
// 		tmp->next = new_node(token[i++]);
// 		if (!tmp->next)
// 			ft_end_list(tokentype);
// 		tmp->next->prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	return (tokentype);
// }

// void	ft_assign_type(t_token *token)
// {
// 	t_token *temp;

// 	temp = token;
// 	while (temp != NULL)
// 	{
// 		if (ft_strncmp(temp->str, "<<", 2) == 0)
// 			temp->type = LESS_LESS;
// 		else if (ft_strncmp(temp->str, ">>", 2) == 0)
// 			temp->type = GREAT_GREAT;
// 		else if (ft_strncmp(temp->str, "<", 1) == 0)
// 			temp->type = LESS;
// 		else if (ft_strncmp(temp->str, ">", 1) == 0)
// 			temp->type = GREAT;
// 		else if (ft_strncmp(temp->str, "|", 1) == 0)
// 			temp->type = PIPE;
// 		else
// 			temp->type = CMD;
// 		temp = temp->next;
// 	}
// }

// t_token *ft_exec_fill(t_token *token, t_init *var)
// {
// 	char **split_token = ft_split(var->input, ' ');
// 	token = ft_fill_list(split_token);
// 	if (!token)
// 	{
// 		printf("Error in fill list token");
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_free_double(split_token);
// 	ft_assign_type(token);

// 	return (token);
// }

void	ft_container_init(t_cmd *container, t_init *var)
{
	container->i = 0;
	container->all_path = find_path(var->envp); // Split PATH= Variable in ENVP
	container->pipe_split = ft_split(var->input, '|'); // Split input at each pipe
	container->cmd_nbr = cmd_counter(container);
}

void	ft_parser(t_init *var)
{
	t_cmd container;

	ft_container_init(&container, var);
	
	container.all_cmd_path = malloc(sizeof(char**) * container.cmd_nbr);
	
	while (container.pipe_split[container.i]) // While there is command.
	{
		container.cmd = ft_split(container.pipe_split[container.i], ' '); // Split the command at each space so cat -e is: cat, -e.
		container.cmd_path = find_cmd_path(container.cmd, container.all_path); // Try to find the path to the command in the ENV variable.
		if (!container.cmd_path)
		{
			error_cmd_path(&container); // BIG CRASH if command not found
			return ;
		}
		container.all_cmd_path[container.i] = container.cmd_path;
		// free(container.cmd_path); // ne pas free cmd_path car sinon impossible a lire dans all_cmd_path. SEGFAULT. free comment ?
		ft_free_double(container.cmd);
		// printf("%s\n", container.all_cmd_path[container.i]);
		container.i++;
	}
	
	// exit(EXIT_FAILURE);
	ft_executor(&container, var->envp);
	
}

	// while (container.pipe_split[container.i]) // While there is command.
	// {
	// 	container.cmd = ft_split(container.pipe_split[container.i], ' '); // Split the command at each space so cat -e is: cat, -e.
	// 	container.cmd_path = find_cmd_path(container.cmd, container.all_path); // Try to find the path to the command in the ENV variable.
	// 	if (!container.cmd_path)
	// 	{
	// 		error_cmd_path(&container);
	// 		return ;
	// 	}
	// 	ft_executor(&container, var->envp); // try to execute the command find in cmd_path.
	// 	free_cmd(&container);
	// 	container.i++;
	// }
	// free_container(&container);
	// token = ft_split(var->input, ' ');
	// tokentype = ft_fill_list(token);
	// ft_free_double(token);
	// ft_assign_type(tokentype);

	// return (tokentype);/42cursus-fract-ol/jupallar