/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-Signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:02:59 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/27 15:58:22 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_ctrlc(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}
