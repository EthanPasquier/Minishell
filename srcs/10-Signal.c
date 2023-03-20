/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-Signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:02:59 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 18:03:04 by jalevesq         ###   ########.fr       */
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

void	ft_ctrld(int sig)
{
	write(1, "\nhello", 6);
	(void)sig;
	// exit(0);
}