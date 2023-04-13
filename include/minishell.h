/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:31:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/13 13:37:34 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include "readline/history.h"
# include <sys/ioctl.h>
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

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_init
{
	char			**envp;
	char			*input;
	char			*tmp;
}					t_init;

typedef struct s_heredoc
{
	int				here_docfd[2];
	int				here_doc_nbr;
	int				flag_doc;
	char			*str;
}					t_heredoc;

typedef struct s_child
{
	int				great_mark;
	int				flag_cmd;
	int				less_mark;
	char			**cmd;
	char			**all_path;
	char			*cmd_path;
	int				pipe_nbr;
	int				cmd_nbr;
	int				*fd_array;
	int				is_builtin;
	int				exit_code;
	int				i;
	int				j;
	t_init			*init;
	t_heredoc		heredoc;
}					t_child;

// Evert function for Parser
t_init		ft_init(char *input);
void		ft_parser(t_child *child);
int			ft_count_parsing(char *str);
int			ft_wake_word(char c);
int			ft_syntax(char *str);
t_token		*new_node(char *str);
int			ft_error_syntax(char *str);
char		*ft_guillemet(char *str, t_child *child);
int			ft_where(char *str, char c, int position);
char		*ft_find_var(char *str, char *vars, t_child *child);
char		*ft_take_var(char *str, int position);
int			ft_ordreguillemet(char *str);
char		*ft_globvar(char *str, char c, t_child *child);
void		ft_ctrlc(int sig);
void		ft_title(void);

int				ft_is_cmd(t_token *token);

/* *** EVERY FUNCTION FOR EXECUTOR *** */

/* MAIN FUNCTION */
void		ft_executor(t_token *token, t_child *child);
void		ft_process_child(t_child *c, t_token *tmp, pid_t *p);

/* CHILD ERROR FUNCTION */
void		ft_child_error(t_token *token, t_child *c, int flag);

/* REDIRECTION && HERE_DOC */
void		ft_less_n_great(t_child *child, t_token *tmp);
void		ft_pipe_child(t_child *child, t_token *token);

void		ft_heredoc(t_token *token, t_child *child, pid_t *pid2);
int			ft_heredoc_nbr(t_token *t);
int			ft_is_doc_last(t_token *token);

/* UTILS FOR EXECUTOR */
char		**ft_find_cmd(t_token *token);
int			*ft_set_pipe(t_child *child);
int			cmd_counter(t_token *token);
void		ft_wait(pid_t *pid, t_child *child);
void		ft_close_fd(int *fd_array, int cmd_nbr);
int			ft_mark_count(t_token *token, int type);
char		*find_cmd_path(t_child *child);
char		**find_path(t_child *child);

/* BUILTIN */

char		*ft_getenv(char **envp, char *var);
char		**ft_copy_env(char **env);
int			ft_is_builtins(t_token *token);
void		ft_which_builtins(t_child *child, t_token *token, pid_t *pid);
void		ft_which_builtins_child(t_child *child, t_token *token);

int			len_equal(char *str);

int			ft_env(t_child *child);
int			ft_cd(t_child *child);
int			ft_pwd(void);
int			ft_unset(t_child *child);
int			ft_export(t_child *child);
void		ft_exit(t_child *child, t_token *token, pid_t *pid);
/*********************************************************/
// Free & End function.
void		ft_free_child(t_token *token, t_child *c);
void		ft_free_child_doc(t_child *child, t_token *token);
void		*ft_free_double(char **str);
void		ft_end_list(t_token *token);
void		ft_free_list(t_token *token);
void		ft_cmd_error(t_child *child);
void		ft_free_exec(char **cmd, char *cmd_path);
#endif