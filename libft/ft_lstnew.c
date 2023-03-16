/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:04:05 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/07 13:04:33 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(*element));
	if (!element)
		return (NULL);
	element->content = content;
	element->next = NULL;
	return (element);
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *item = ft_lstnew((void *)4);
// 	printf("%d\n", (int)item->content);
// }