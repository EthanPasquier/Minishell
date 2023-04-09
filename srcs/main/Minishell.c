/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:32:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/09 15:45:45 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_readline(char **envp)
{
	char	*input;
	t_init	*var;

	var = malloc(sizeof(t_init));
	var->envp = ft_copy_env(envp);
	signal(SIGINT, ft_ctrlc);
	while (1)
	{
		input = readline("\U0001F9E0 \033[1;36mminishell > \033[0m");
		if (input)
		{
			if (ft_strlen(input) > 0)
			{
				add_history(input);
				var->input = input;
				ft_parser(var);
				free(input);
			}
		}
		else
		{
			ft_free_double(var->envp);
			free(var);
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