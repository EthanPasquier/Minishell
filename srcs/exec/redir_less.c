/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/05 11:06:30 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_heredoc(t_token *token)
// {
// 	char	*str;
// 	char	*tmp;

// 	tmp = NULL;
// 	while (1)
// 	{
// 		str = readline(">");
// 		if (ft_strncmp(str, token->next->str, ft_strlen(token->next->str)) == 0
// 		&& ft_strlen(token->next->str) == ft_strlen(str))
// 			break;
// 		tmp = str;
// 		str = ft_strjoin(str, "\n");
// 		free(tmp);
// 	}
// 	fprintf(stderr, "%s", tmp);
// }

void ft_less_child(t_child *child, t_token *token, int less)
{
	int		fd;

	fd = -1;
	if (token->type == LESS)
	{
		fd = open(token->next->str, O_RDONLY);
			if (fd == -1)
				ft_child_error(token, child, ERR_OPEN);
		if (less == child->less_mark)
		{
			if (dup2(fd, STDIN) == -1)
			{
				close(fd);
				ft_child_error(token, child, ERR_DUP2);
			}
		}
		close(fd);	
	}
}

	// Work for one here_doc, if one pipe, crashing.
	// else if (token->type == LESS_LESS)
	// {
	// 	char *str;
	// 	if (less == child->less_mark)
	// 	{
	// 		if (pipe(child->here_docfd) == -1)
	// 			ft_error(1); // Close all fd and exit child process
	// 	}
	// 	while (1)
	// 	{
	// 		str = readline(">");
	// 		if (ft_strncmp(str, token->next->str, ft_strlen(token->next->str)) == 0
	// 		&& ft_strlen(token->next->str) == ft_strlen(str))
	// 		break;
	// 		if (less == child->less_mark)
	// 		{
	// 			write(child->here_docfd[1], str, ft_strlen(str));
	// 			write(child->here_docfd[1], "\n", 1);
	// 		}
	// 		free(str);
	// 	} 
	// 	if (less == child->less_mark)
	// 	{
	// 		if (dup2(child->here_docfd[0], STDIN) == -1)
	// 		{
	// 			close(child->here_docfd[0]); // close read end
	// 			close(child->here_docfd[1]); // close write end
	// 			ft_child_error(token, child, ERR_DUP2);
	// 		}
	// 		close(child->here_docfd[0]); // close read end
	// 		close(child->here_docfd[1]); // close write end
	// 	}
	// }
