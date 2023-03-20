/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01-Minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:32:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 10:21:50 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// main boucle ? Ne jamais en sortir pour toujours redonner le terminal ?
void	ft_readline(char **envp)
{
	char	*input;
	// t_token	*token;
	t_init	var;

	// token = NULL;
	while (1)
	{
		input = readline("\U0001F9E0 \033[1;36mminishell > \033[0m");
		if (ft_strlen(input) > 0) // Peut causer des problèmes ? Cas particulier? Trouver une autre condition ?
		{
			var = ft_init(input, envp);
			ft_parser(&var, NULL);
			// token = ft_parser(&var, token);
			// ft_free_list(token);
			free(input);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_readline(envp);
}

		// t_token *tmp;
		// tmp = token;
		// while (tmp)
		// {
		// 	printf("%s\n", tmp->str);
		// 	printf("%d\n", tmp->type); //pour print les valeurs dans linked list et faire des tests.
		// 	tmp = tmp->next;
		// }

// if (ft_strncmp(input, "exit", 4) == 0)
// {
// 	printf("exit\n");
// 	free(input);
// 	exit(EXIT_FAILURE);
// }