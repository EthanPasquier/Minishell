/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:31:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/16 11:49:03 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>

# define CMD 1
# define ARG 2
# define GREAT 3
# define GREAT_GREAT 4
# define LESS 5
# define LESS_LESS 6

typedef struct s_init {
	char 	**envp;
	char	*input;
}	t_init;

typedef struct s_token {
	char *str;
	int type;
	struct s_token *next;
}	t_token;

t_init	ft_init(char **envp, char *input);
t_token	*new_node(char *str);
t_token	*ft_parser(t_init *var, t_token *tokentype);

char	**lexer(char const *s);

// Free & End function.
void	*ft_free_double(char **str);
void	ft_free_list(t_token *token);
void	ft_error(int flag);

#endif