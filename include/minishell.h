/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:31:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/20 10:58:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define CMD 1
# define ARG 2
# define GREAT 3
# define GREAT_GREAT 4
# define LESS 5
# define LESS_LESS 6
# define PIPE 7

typedef struct s_init
{
	char			**envp;
	char			*input;
}					t_init;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd {
	char	**pipe_split;
	char	**cmd;
	char	**all_path;
	char	*cmd_path;
}	t_cmd;

t_init				ft_init(char *input, char **envp);
t_token				*new_node(char *str);
void				ft_parser(t_init *var);

char 				**find_path(char **envp);
char				*find_cmd_path(char **cmd, char **path);

void	ft_executor(t_cmd *command, t_init *var);

// Free & End function.
void				*ft_free_double(char **str);
void				free_container(t_cmd *container);
void				ft_free_list(t_token *token);
void				ft_error(int flag);

#endif