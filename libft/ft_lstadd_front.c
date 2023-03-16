/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:49:19 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/07 15:10:12 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *item1;
// 	t_list *item2;
// 	t_list *item3;
// 	t_list *item4;
// 	t_list *new;
// 	t_list *head;

// 	new = (t_list *)malloc(sizeof(*new));
// 	item1 = (t_list *)malloc(sizeof(*item1));
// 	item2 = (t_list *)malloc(sizeof(*item2));
// 	item3 = (t_list *)malloc(sizeof(*item3));
// 	item4 = (t_list *)malloc(sizeof(*item4));

// 	new->content = (void *)10;
// 	item1->content = (void *)20;
// 	item2->content = (void *)30;
// 	item3->content = (void *)40;
// 	item4->content = (void *)50;

// 	item1->next = item2;
// 	item2->next = item3;
// 	item3->next = item4;
// 	item4->next = NULL;
// 	head = item1;

// 	ft_lstadd_front(&head, new);
// 	while (new)
// 	{
// 		printf("%d\n", (int)new->content);
// 		new = new->next;
// 	}
// }