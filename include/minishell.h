/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:31:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/29 14:20:44 by jalevesq         ###   ########.fr       */
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
# define FILE 8

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

typedef struct s_child
{
	char **envp;
	char **cmd;
	char **all_path;
	char *cmd_path;
	int i;
	int	j;
	int cmd_nbr;
}					t_child;

t_init				ft_init(char *input, char **envp);
t_token				*new_node(char *str);

void				ft_parser(t_init *var);
char				**ft_split_input(char *s);
int					ft_wake_word(char c);


char				**find_path(char **envp);
char				*find_cmd_path(char **cmd, char **path);

void				ft_ctrlc(int sig);
void				ft_title(void);
// int				ft_is_next_pipe(t_token *tmp_cmd);
// int				ft_is_prev_pipe(t_token *tmp_cmd);


// Every function for Executor
void				ft_executor(t_token *token, char **envp);
int					cmd_counter(t_token *token);
void				ft_wait(pid_t *pid, int cmd_nbr);
int					*ft_set_pipe(t_child *child);
void				ft_process_child(t_child *c, t_token *tmp, int *fd, int *pid);
void				ft_exec_child(t_child *child, t_token *token, int *fd);
void				ft_close_child(int *fd_array, int cmd_nbr);
void				ft_child_pipe(t_child *c, t_token *t, int *fd);
void				ft_child_great_front(t_token *t);
void				ft_multiple_great_front(int *fd2, t_token *tmp);
void				ft_child_great_back(t_token *t);

// Free & End function.
void				*ft_free_double(char **str);
void				ft_end_list(t_token *token);
void				ft_free_list(t_token *token);
void				ft_error(int flag);
void				ft_free_exec(char **cmd, char *cmd_path);
// void				free_container(t_cmd *container);
// void				error_cmd_path(t_cmd *container);
// void				free_cmd(t_cmd *container);

#endif