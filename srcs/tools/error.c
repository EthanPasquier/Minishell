/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:26:15 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/21 15:28:43 by epasquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_free_double(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
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
			if (token->str)
				free(token->str);
			token->str = NULL;
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

void	ft_cmd_error(t_child *child)
{
	write(2, "minishell: ", 11);
	if (!child->cmd[0])
		write(2, " ", 1);
	else
		write(2, child->cmd[0], ft_strlen(child->cmd[0]));
	write(2, ": command not found\n", 20);
}

void	ft_end_list(t_token *token)
{
	ft_free_list(token);
	write(2, "Error in filling the token list.", 32);
	exit(EXIT_FAILURE);
}
