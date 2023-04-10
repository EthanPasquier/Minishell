/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:32:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/10 17:22:55 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_readline(char **envp)
{
	t_child	*child;

	child = malloc(sizeof(t_child));
	child->init = malloc(sizeof(t_init));
	child->init->envp = ft_copy_env(envp);
	signal(SIGINT, ft_ctrlc);
	while (1)
	{
		
		child->init->input = readline("\U0001F9E0 \033[1;36mminishell > \033[0m");
		if (child->init->input)
		{
			if (ft_strlen(child->init->input) > 0)
			{
				add_history(child->init->input);
				ft_parser(child);
				free(child->init->input);
			}
		}
		else
		{
			ft_free_double(child->init->envp);
			free(child->init);
			free(child);
			exit(EXIT_SUCCESS);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_title();
	ft_readline(envp);
}

// if (ft_strncmp(input, "exit", 4) == 0)
// {
// 	printf("exit\n");
// 	free(input);
// 	exit(EXIT_FAILURE);
// }