/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01-Minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:32:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 14:33:31 by epasquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// // void	ft_ctrlc(int sig)
// // {
// // 	(void)sig;
// // 	rl_redisplay();
// // 	rl_newline(0, 0); //petit test
// // }

// // main boucle ? Ne jamais en sortir pour toujours redonner le terminal ?
// void	ft_readline(char **envp)
// {
// 	char	*input;
// 	t_init	var;

// 	// t_token	*token;
// 	// token = NULL;
// 	while (1)
// 	{
// 		input = readline("\U0001F9E0 \033[1;36mminishell > \033[0m");
// 		if (ft_strlen(input) > 0)
// 		// Peut causer des problèmes ? Cas particulier? Trouver une autre condition ?
// 		{
// 			var = ft_init(input, envp);
// 			ft_parser(&var);
// 			// token = ft_parser(&var, token);
// 			// ft_free_list(token);
// 			free(input);
// 		}
// 	}
// }

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

#include <signal.h>

void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(2, "\n", 1);
	rl_redisplay();
}

void	ft_readline(char **envp)
{
	char	*input;
	t_init	var;

	signal(SIGINT, handle_sigint);
	while (1)
	{
		input = readline("\U0001F9E0 \033[1;36mminishell > \033[0m");
		if (ft_strlen(input) > 0)
		{
			var = ft_init(input, envp);
			ft_parser(&var);
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