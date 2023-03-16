/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-Token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/16 11:48:56 by jalevesq         ###   ########.fr       */
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

t_token	*ft_parser(t_init *var, t_token *tokentype)
{
	char	**token;
	t_token *temp;

	token = lexer(var->input); // ft_token(var) AKA fonction de Ethan
	tokentype = ft_fill_list(token);
	ft_free_double(token);
	temp = tokentype;
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
		else
			temp->type = CMD;
		temp = temp->next;
	}
	return (tokentype);
}