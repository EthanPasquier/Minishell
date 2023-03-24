/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01-Minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:32:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/24 14:27:09 by epasquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_readline(char **envp)
{
	char	*input;
	t_init	var;

	signal(SIGINT, ft_ctrlc);
	// signal(SIGQUIT, ft_ctrld);
	while (1)
	{
		input = readline("\U0001F9E0 \033[1;36mminishell > \033[0m");
		if (input)
		{
			if (ft_strlen(input) > 0)
			// leak car résultat de strtrim non stocké ?
			{
				add_history(input);
				var = ft_init(input, envp);
				ft_parser(&var);
				free(input);
			}
		}
		else
			exit(EXIT_SUCCESS); // changer, des trucs à free, clear history ? ?
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_title();
	ft_readline(envp);
}

// t_token *tmp;
// tmp = token;
// while (tmp)
// {
// 	printf("%s\n", tmp->str);
// 	printf("%d\n", tmp->type);
		//pour print les valeurs dans linked list et faire des tests.
// 	tmp = tmp->next;
// }

// if (ft_strncmp(input, "exit", 4) == 0)
// {
// 	printf("exit\n");
// 	free(input);
// 	exit(EXIT_FAILURE);
// }