/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/29 15:52:00 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Error func good ?
t_token	*ft_fill_list(char **split_input)
{
	t_token	*token;
	t_token	*tmp;
	int		i;

	i = 0;
	token = new_node(split_input[i++]);
	token->prev = NULL;
	tmp = token;
	while (split_input[i])
	{
		tmp->next = new_node(split_input[i++]);
		if (!tmp->next)
			ft_end_list(token);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	return (token);
}

void	ft_assign_type(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->str, "<<", 2) == 0)
			temp->type = LESS_LESS;
		else if (ft_strncmp(temp->str, ">>", 2) == 0)
			temp->type = GREAT_GREAT;
		else if (ft_strncmp(temp->str, "<", 1) == 0)
			temp->type = LESS;
		else if (ft_strncmp(temp->str, ">", 1) == 0)
			temp->type = GREAT;
		else if (ft_strncmp(temp->str, "|", 1) == 0)
			temp->type = PIPE;
		else
			temp->type = CMD;
		if (temp->type == CMD && temp->prev && temp->prev->type == GREAT )
			temp->type = FILE;
		temp = temp->next;
	}
}

char	*ft_find_var(char **envp, char *var)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0)
		{
			var = ft_strtrim(envp[i], var);
			break ;
		}
		i++;
	}
	return (var);
}

int	ft_where(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*ft_take_var(char *str, int position)
{
	int		i;
	int		nb;
	char	*var;

	i = position;
	while (str[i])
	{
		if (ft_wake_word(str[i]) == 1 || str[i] == ' ' || str[i] == 39 || str[i] == 34)
			break ;
		i++;
	}
	nb = i - position;
	var = malloc((sizeof(char) * nb) + 2);
	i = 0;
	while (i < nb)
	{
		var[i] = str[position];
		i++;
		position++;
	}
	var[i] = '=';
	return (var);
}

char	*ft_redifine(char *mots, char *str, char sign)
{
	int		a;
	int		b;
	int		c;
	int		tmp;
	char	*new;

	a = 0;
	b = 0;
	c = 0;
	while (str[a] != sign && str[a])
		a++;
	c = a;
	while ((str[c] != 32 && ft_wake_word(str[c]) == 0 && str[c] != 39 && str[c] != 34) && str[c])
	{
		c++;
		b++;
	}
	tmp = c;
	c = (ft_strlen(str) - b + ft_strlen(mots));
	new = malloc((sizeof(char) * c) + 1);
	b = 0;
	while (b < a)
	{
		new[b] = str[b];
		b++;
	}
	c = ft_strlen(mots);
	a = 0;
	while (a < c)
	{
		new[b] = mots[a];
		b++;
		a++;
	}
	while (str[tmp])
	{
		new[b] = str[tmp];
		b++;
		tmp++;
	}
	return (new);
}

void	ft_parser(t_init *var)
{
	t_token	*token;
	char	**split;
	int		a;
	char	*mots;

	mots = NULL;
	a = ft_where(var->input, '$');
	while (a != -1)
	{
		mots = ft_take_var(var->input, a);
		// fprintf(stderr, "\nmots = %s\n", mots);
		mots = ft_find_var(var->envp, mots);
		var->input = ft_redifine(mots, var->input, '$');
		a = ft_where(var->input, '$');
	}
	split = ft_split_input(var->input);
	token = ft_fill_list(split);
	ft_free_double(split);
	ft_assign_type(token);
	// t_token *tmp = token;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->str);
	// 	printf("%d\n", tmp->type);
	// 	// pour print les valeurs dans linked list et faire des tests.
	// 	tmp = tmp->next;
	// }
	// exit(EXIT_FAILURE);
	ft_executor(token, var->envp);
	ft_free_list(token);
}