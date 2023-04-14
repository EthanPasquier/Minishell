/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:32:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/13 19:32:13 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_good_input(t_child *child)
{
	if (ft_strlen(child->init->input) > 0)
	{
		add_history(child->init->input);
		ft_parser(child);
		free(child->init->input);
	}
}

static void ctrld(t_child *child)
{
	printf("exit\n");
	ft_free_double(child->init->envp);
	free(child->init);
	free(child);
	exit(EXIT_SUCCESS);
}

void	ft_readline(char **envp)
{
	t_child	*child;

	child = malloc(sizeof(t_child));
	child->init = malloc(sizeof(t_init));
	child->init->envp = ft_copy_env(envp);
	child->exit_code = 0;
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		child->init->input = readline("minishell > ");
		if (child->init->input)
			ft_good_input(child);
		else
			ctrld(child);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_title();
	ft_readline(envp);
}