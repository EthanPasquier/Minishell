/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-Parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/17 10:27:20 by jalevesq         ###   ########.fr       */
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

t_token	*ft_parser(t_init *var, t_token *tokentype)
{
	char	**token;
	// char	**path;
	
	token = ft_split(var->input, ' ');	// lexer(var->input); AKA fonction de Ethan
	tokentype = ft_fill_list(token);
	ft_free_double(token);
	ft_assign_type(tokentype);
	// printf("%s\n", var->envp[0]);
	// path = find_path(var); // Find path ne marche pas, init envp ne fontionne plus.

	// Trouver comment faire un AST


	return (tokentype);
}

