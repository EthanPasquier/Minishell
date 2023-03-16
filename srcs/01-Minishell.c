/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01-Minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:32:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/16 11:55:43 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Rappeler readline à chaque fin de commande exécuter, ne pas mettre tout dans la boucle ?
void	ft_readline(char **envp)
{
	char	*input;
	t_token	*token;
	t_init	var;

	token = NULL;
	while (1)
	{
		input = readline("\U0001F9E0 \033[1;36mminishell > \033[0m");
		if (ft_strlen(input) > 0)
		{
			var = ft_init(envp, input);
			token = ft_parser(&var, token);
		}
		// t_token *tmp;
		// tmp = token;
		// while (tmp)
		// {
		// 	printf("%s\n", tmp->str); // pour print les valeurs dans linked list et faire des tests.
		// 	printf("%d\n", tmp->type);
		// 	tmp = tmp->next;
		// }
		ft_free_list(token);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_readline(envp);
}

			// if (ft_strncmp(input, "exit", 4) == 0)
			// {
			// 	printf("exit\n");
			// 	free(input);
			// 	exit(EXIT_FAILURE);
			// }