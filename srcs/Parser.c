/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/28 11:07:20 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Error func good ?
t_token	*ft_fill_list(char **split_input)
{
	t_token	*token;
	t_token	*tmp;
	int		i;

	i = 0;
	token = new_node(split_input[i++]);
	token->prev = NULL;
	tmp = token;
	while (split_input[i])
	{
		tmp->next = new_node(split_input[i++]);
		if (!tmp->next)
			ft_end_list(token);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	return (token);
}

void	ft_assign_type(t_token *token)
{
	t_token	*temp;

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
		if (temp->type == CMD && temp->prev
			&& temp->prev->type == GREAT)
			temp->type = FILE;
		temp = temp->next;
	}
}

void	ft_parser(t_init *var)
{
	t_token	*token;
	char	**split;

	split = split_input(var->input, ' ');

	token = ft_fill_list(split);
	ft_free_double(split);
	ft_assign_type(token);

	t_token *tmp;
	tmp = token;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->str);
	// 	printf("%d\n", tmp->type);
	// 	// pour print les valeurs dans linked list et faire des tests.
	// 	tmp = tmp->next;
	// }
	// exit(EXIT_FAILURE);
	ft_executor(token, var->envp);
	ft_free_list(token);
}