/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:32:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/19 16:28:49 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_code;

static char	*find_trash_path(char **envp)
{
	char	*user;
	char	*home;
	char	*trash_path;
	char	*tmp;

	user = ft_getenv(envp, "USER=");
	if (user != NULL)
	{
		tmp = ft_strdup("/Users/");
		trash_path = ft_strjoin(tmp, user);
		free(tmp);
		free(user);
		tmp = ft_strjoin(trash_path, "/.Trash");
		free(trash_path);
		return (tmp);
	}
	else
	{
		free(user);
		home = ft_getenv(envp, "HOME=");
		if (home != NULL)
			return (home);
	}
	free(user);
	return (NULL);
}

static void	ctrld(t_child *child)
{
	printf("exit\n");
	rl_clear_history();
	ft_free_double(child->init->envp);
	free(child->trash_path);
	free(child->init);
	free(child);
	exit(EXIT_SUCCESS);
}

static void	ft_good_input(t_child *child)
{
	if (ft_strlen(child->init->input) > 0
		&& ft_is_only_space(child->init->input))
	{
		add_history(child->init->input);
		ft_parser(child);
		if (child->init->input)
			free(child->init->input);
	}
}

static void	ft_readline(char **envp)
{
	t_child	*child;

	child = malloc(sizeof(t_child));
	child->init = malloc(sizeof(t_init));
	child->init->envp = ft_copy_env(envp);
	child->trash_path = find_trash_path(child->init->envp);
	child->exit_code = 0;
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_exit_code = 0;
		child->init->input = readline("minishell > ");
		if (child->init->input)
		{
			if (g_exit_code != 0)
				child->exit_code = g_exit_code;
			ft_good_input(child);
		}
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
