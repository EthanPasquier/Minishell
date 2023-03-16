/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 04:07:36 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/07 14:11:23 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (del && lst)
	{
		while (*lst)
		{
			temp = *lst;
			*lst = temp->next;
			ft_lstdelone(temp, del);
		}
	}
}
