/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:06:03 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/30 15:06:36 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_error_syntax(char c)
{
    fprintf(stderr, "minishell: syntax error near: [%c]\n", c);
    return (1);
}

int ft_syntax(char *str)
{
    int i;
    int tmp;
    i = 0;
    tmp = 0;
    while (str[i])
    {
        if (str[i] == 39 || str[i] == 34)
            tmp++;
        i++;
    }
    if (tmp % 2 != 0)
        return (ft_error_syntax('"'));
    return (0);
}