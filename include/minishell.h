/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epasquie <epasquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:31:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/24 14:28:19 by epasquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <signal.h>
# include <stdlib.h>
# include <string.h>

# define CMD 1
# define ARG 2
# define GREAT 3
# define GREAT_GREAT 4
# define LESS 5
# define LESS_LESS 6
# define PIPE 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd
{
	char			**pipe_split;
	char			**cmd;
	char			**all_path;
	char			*cmd_path;
	char			**all_cmd_path;
	int				i;
	int				cmd_nbr;
	pid_t			pid;
}					t_cmd;

t_init				ft_init(char *input, char **envp);
t_token				*new_node(char *str);
void				ft_parser(t_init *var);

int					*ft_set_pipe(t_cmd *container);
void				ft_close_child(int *fd_array, int cmd_nbr);

char				**find_path(char **envp);
char				*find_cmd_path(char **cmd, char **path);

void				ft_ctrlc(int sig);
void				ft_ctrld(int sig);
int					cmd_counter(t_cmd *container);
void				ft_title(void);
// int					ft_is_next_pipe(t_token *tmp_cmd);
// int					ft_is_prev_pipe(t_token *tmp_cmd);

// void				ft_executor(t_cmd *container, t_init *var, t_token *token);
void				ft_executor(t_cmd *container, char **envp);

// Free & End function.
void				*ft_free_double(char **str);
void				free_container(t_cmd *container);
void				ft_free_list(t_token *token);
void				ft_error(int flag);
void				error_cmd_path(t_cmd *container);
void				free_cmd(t_cmd *container);
void				ft_end_list(t_token *token);

#endif