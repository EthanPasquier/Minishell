/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:31:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/03 20:14:57 by jalevesq         ###   ########.fr       */
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

// Define type in linked list
# define CMD 1
# define GREAT 2
# define GREAT_GREAT 3
# define LESS 4
# define LESS_LESS 5
# define PIPE 6
# define FILE 7

// Error code.
# define ERR_EXECVE 1
# define ERR_OPEN 2
# define ERR_DUP2 3
# define ERR_PID 4

// Standard fd
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
	int	great_mark;
	int	less_mark;
	char **envp;
	char **cmd;
	char **all_path;
	char *cmd_path;
	int	pipe_nbr;
	int cmd_nbr;
	int	*fd_array;
	int i;
	int	j;
}					t_child;


// Evert function for Parser
t_init				ft_init(char *input, char **envp);
void				ft_parser(t_init *var);
int					ft_count_parsing(char *str);
int					ft_wake_word(char c);
int					ft_syntax(char *str);
int					ft_error_syntax(char *str);
t_token				*new_node(char *str);


void				ft_ctrlc(int sig);
void				ft_title(void);

int	ft_is_cmd(t_token *token);

// Every function for Executor
void				ft_executor(t_token *token, char **envp);
void				ft_process_child(t_child *c, t_token *tmp, int *pid);

int					*ft_set_pipe(t_child *child);
int					cmd_counter(t_token *token);
void				ft_wait(pid_t *pid, int cmd_nbr);
void				ft_close_fd(int *fd_array, int cmd_nbr);
int					ft_mark_count(t_token *token, int type);

void				ft_child_error(t_token *token, t_child *c, int flag);

void				ft_great_child(t_child *child, t_token *token, int great);
void				ft_less_child(t_child *child, t_token *token, int less);
void				ft_pipe_child(t_child *child, t_token *token);

// These are for when there is no cmd, only redirection
void				ft_child_redirection_front(t_token *token, t_child *c);
void				ft_child_redirection_back(t_token *token, t_child *c);
void				ft_type_great(t_token *tmp, int *flag, int *fd2);
void				ft_type_less(t_token *tmp, int *flag, int *fd2);
t_token				*ft_next_redir(t_token *token);

char				*find_cmd_path(char **cmd, char **path);
char				**find_path(char **envp);


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