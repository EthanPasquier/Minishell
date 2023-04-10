/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:26:15 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/09 15:49:39 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
	return (NULL);
}

void	ft_free_list(t_token *token)
{
	t_token	*tmp;

	if (token)
	{
		while (token)
		{
			tmp = token->next;
			free(token->str); // free le strdup dans new_node
			free(token);
			token = tmp;
		}
	}
}

void	ft_free_exec(char **cmd, char *cmd_path)
{
	if (cmd != NULL)
		ft_free_double(cmd);
	if (cmd_path != NULL)
		free(cmd_path);
	cmd = NULL;
	cmd_path = NULL;
}

void	ft_error(int flag)
{
	if (flag == 1)
		printf("wtf\n");
	printf("ERROR\n");
	exit(EXIT_SUCCESS);
}

void	ft_end_list(t_token *token)
{
	ft_free_list(token);
	printf("Error in filling the token list.");
	exit(EXIT_FAILURE);
}

// void	ft_end_list_env(t_env *env)
// {
// 	t_env	*tmp;

// 	if (env)
// 	{
// 		while (env)
// 		{
// 			tmp = env->next;
// 			free(env->envp); // free le strdup dans new_node
// 			free(env);
// 			env = tmp;
// 		}
// 	}
// 	printf("Error in filling the env list.");
// 	exit(EXIT_SUCCESS);
// }