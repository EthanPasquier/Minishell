/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:48:06 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/20 13:39:40 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_where(char *str, char c, int position)
{
	int	i;

	i = position;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*ft_resize(char *str)
{
	char	*newstr;

	free(str);
	newstr = ft_calloc(2, sizeof(char));
	newstr[0] = '|';
	return (newstr);
}

int	ft_issimplearg(char *str, int i)
{
	if (str[i] == '-')
	{
		if (str[i + 1] == 'n')
		{
			if (str[i + 2] == 32 || str[i + 2] == 29)
			{
				if (str[i - 1] == 32 || str[i - 1] == 29)
				{
					return (1);
				}
			}
		}
	}
	return (0);
}

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
		if (temp->type == CMD && (temp->prev && (temp->prev->type == GREAT
					|| temp->prev->type == GREAT_GREAT
					|| temp->prev->type == LESS_LESS
					|| temp->prev->type == LESS)))
			temp->type = FILE;
		temp = temp->next;
	}
}
