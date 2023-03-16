/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:15:43 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/04 04:11:59 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *item1;
// 	t_list *item2;
// 	t_list *item3;
// 	t_list *item4;
// 	t_list *head;

// 	item1 = (t_list *)malloc(sizeof(*item1));
// 	item2 = (t_list *)malloc(sizeof(*item2));
// 	item3 = (t_list *)malloc(sizeof(*item3));
// 	item4 = (t_list *)malloc(sizeof(*item4));

// 	item1->content = (void *)20;
// 	item2->content = (void *)30;
// 	item3->content = (void *)40;
// 	item4->content = (void *)50;

// 	item1->next = item2;
// 	item2->next = item3;
// 	item3->next = item4;
// 	item4->next = NULL;
// 	head = item1;

// 	printf("%d\n", ft_lstsize(head));
// }