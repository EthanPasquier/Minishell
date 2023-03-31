/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/31 15:34:29 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void file_does_not_exist(t_token *tmp)
{
	perror(tmp->next->str);
	exit(EXIT_SUCCESS);

}

