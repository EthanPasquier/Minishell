/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:02:59 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/12 08:54:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n"); // print a newline character
		rl_on_new_line(); // move to a new line in readline
		rl_replace_line("", 0); // clear the current input line
		rl_redisplay(); // redisplay the prompt
	}
}