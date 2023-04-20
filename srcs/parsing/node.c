/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:11:19 by epasquie          #+#    #+#             */
/*   Updated: 2023/04/20 13:38:53 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_insertnode_suite(int character)
{
	char	*newdata;

	newdata = ft_calloc(sizeof(char), 4);
	if (character == 2 || character == 4)
		newdata[0] = '<';
	if (character == 3 || character == 5)
		newdata[0] = '>';
	if (character == 4)
		newdata[1] = '<';
	if (character == 5)
		newdata[1] = '>';
	return (newdata);
}

void	ft_insertnode(t_token *head, int character, int position)
{
	t_token	*newnode;
	t_token	*currentnode;
	int		i;
	char	*newnata;

	newnode = (t_token *)malloc(sizeof(t_token));
	newnata = ft_insertnode_suite(character);
	newnode->str = newnata;
	currentnode = head;
	i = 1;
	while (i < position && currentnode != NULL)
	{
		currentnode = currentnode->next;
	}
	if (currentnode == NULL)
	{
		printf("error link list in parser\n");
		return ;
	}
	newnode->next = currentnode->next;
	currentnode->next = newnode;
	newnode->prev = currentnode;
	if (newnode->next != NULL)
		newnode->next->prev = newnode;
}
