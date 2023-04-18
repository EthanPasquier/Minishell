/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:23:24 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/18 08:46:26 by jalevesq         ###   ########.fr       */
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
		if (temp->type == CMD && (temp->prev && (temp->prev->type == GREAT
					|| temp->prev->type == GREAT_GREAT
					|| temp->prev->type == LESS_LESS
					|| temp->prev->type == LESS)))
			temp->type = FILE;
		temp = temp->next;
	}
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
	// printf("str = %s\nmots = %s\n", str, mots);
	while (str[a] != sign && str[a])
		a++;
	c = a + 1;
	while (str[c] != 32 && ft_wake_word(str[c]) == 0 && str[c] != 39
		&& str[c] != 34 && str[c] != '$' && str[c] != 45 && str[c] != 43
		&& str[c])
	{
		c++;
		b++;
	}
	tmp = c;
	c = (ft_strlen(str) - b + ft_strlen(mots));
	// new = malloc((sizeof(char) * c) + 1);
	new = ft_calloc(sizeof(char), c + 1);
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
	new[b] = 0;
	return (new);
}

char	*ft_rmword(char const *str, char const *mots)
{
	size_t	size;
	int		i;
	int		j;
	char	*final;

	if (str == NULL || mots == NULL)
		return (NULL);
	size = ft_strlen(str) - ft_strlen(mots) + 1;
	final = ft_calloc(sizeof(char), size);
	i = 0;
	j = ft_strlen(mots);
	while (i < (int)size)
	{
		final[i] = str[j];
		i++;
		j++;
	}
	return (final);
}

char	*ft_find_var(char *str, char *vars, t_child *child)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (child->init->envp[i])
	{
		if (ft_strncmp(vars, child->init->envp[i], ft_strlen(vars)) == 0)
		{
			vars = ft_rmword(child->init->envp[i], vars);
			new = ft_redifine(vars, str, '$');
			// printf("selection = %s\n", new);
			free(str);
			free(vars);
			return (new);
		}
		i++;
	}
	if (!new)
	{
		if (vars[0] == '?' && vars[1] == '=' && vars[2] == 0)
		{
			vars = ft_itoa(child->exit_code);
			new = ft_redifine(vars, str, '$');
			free(str);
			free(vars);
			return (new);
		}
	}
	return (str);
}

int	ft_where(char *str, char c, int position)
{
	int	i;

	i = position;
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
	// printf("position = %s\n", str);
	while (str[i] != 0)
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '?')
		{
			// printf("str[i] = %c\n", str[i]);
			break ;
		}
		i++;
	}
	if (ft_isalpha(str[i]) == 0 && str[i] != '?')
		i--;
	// printf("i = %d\n", i);
	nb = i - position + 2;
	// printf("rtailel = %d\n", nb);
	// printf("i = %d\n", i);
	// printf("position = %d\n", position);
	// printf("nb = %d\n", nb);
	// var = malloc((sizeof(char) * nb) + 2);
	var = ft_calloc(sizeof(char), nb + 1);
	i = 0;
	while (i < nb - 1)
	{
		var[i] = str[position];
		// printf("var = %s\n", var);
		i++;
		position++;
	}
	var[i] = '=';
	// printf("var = %s\n", var);
	return (var);
}

char	*ft_chevronparsing(char *str, int i)
{
	// int	j;
	// j = 0;
	while (str[i] == 32)
		i++;
	while ((ft_wake_word(str[i]) > 0 || str[i] == 32) && str[i])
		i++;
	while ((ft_wake_word(str[i]) == 0 && str[i] != 32 && str[i] != 29)
		&& str[i])
		i++;
	if (i < (int)ft_strlen(str) && ft_wake_word(str[i]) == 0)
		str[i] = 29;
	return (str);
}

char	*ft_write_cut(char *str)
{
	int		i;
	int		j;
	int		tmp;
	int		count;
	char	*output;

	// char	*tmp;
	// int		temoins;
	i = 0;
	j = 0;
	count = ft_count_parsing(str);
	// printf("count = %d\n", count);
	output = ft_calloc(sizeof(char), (ft_strlen(str) + count) + 1);
	// temoins = 0;
	str[ft_strlen(str)] = 0;
	tmp = 1;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			tmp++;
		if (ft_wake_word(str[i]) >= 1 && tmp % 2 != 0)
		{
			if (ft_wake_word(str[i]) == 2)
				str = ft_chevronparsing(str, i + 1);
			if (i > 0)
			{
				output[j] = 29;
				j++;
			}
			while (ft_wake_word(str[i]) >= 1 || str[i] == 32)
			{
				if (ft_wake_word(str[i]) == 2)
					str = ft_chevronparsing(str, i + 1);
				output[j] = str[i];
				j++;
				i++;
			}
			output[j] = 29;
		}
		else
		{
			output[j] = str[i];
			i++;
		}
		j++;
	}
	return (output);
}

void	ft_insertNode(t_token *head, int character, int position)
{
	t_token	*newNode;
	t_token	*currentNode;
	int		i;
	char	*newData;

	newNode = (t_token *)malloc(sizeof(t_token));
	newData = ft_calloc(sizeof(char), 4);
	if (character == 2 || character == 4)
		newData[0] = '<';
	if (character == 3 || character == 5)
		newData[0] = '>';
	if (character == 4)
		newData[1] = '<';
	if (character == 5)
		newData[1] = '>';
	newNode->str = newData;
	currentNode = head;
	i = 1;
	while (i < position && currentNode != NULL)
	{
		currentNode = currentNode->next;
		i++;
	}
	if (currentNode == NULL)
	{
		printf("error link list in parser\n");
		return ;
	}
	newNode->next = currentNode->next;
	currentNode->next = newNode;
	newNode->prev = currentNode;
	if (newNode->next != NULL)
		newNode->next->prev = newNode;
}

char	*ft_resize(char *str)
{
	char	*newstr;

	free(str);
	newstr = ft_calloc(2, sizeof(char));
	newstr[0] = '|';
	return (newstr);
	return (newstr);
}

int	ft_issimplearg(char *str, int i)
{
	if (str[i] == '-')
	{
		if (str[i + 1] == 'n')
		{
			if (str[i + 2] == 32 || str[i + 2] == 29)
			{
				if (str[i - 1] == 32 || str[i - 1] == 29)
				{
					return (1);
				}
			}
		}
	}
	return (0);
}

char	*ft_echoargument(char *str, int i)
{
	int		tmp;
	int		j;
	int		nb;
	char	*new;

	// int		j;
	tmp = 0;
	nb = 0;
	while (i >= 0)
	{
		i = ft_where(str, '-', i) - 1;
		if (i > -1 && ft_issimplearg(str, i) == 1)
			i++;
		else
			break ;
		tmp++;
	}
	// printf("i = %d\ntmp = %d\n", i, tmp);
	if (i <= 0 && tmp <= 1)
		return (str);
	i++;
	tmp = 0;
	new = ft_strdup(str);
	j = i;
	while (str[i] && str[i] != 32)
	{
		if (str[i] == 'n' && str[i - 1] != '-')
		{
			str[i] = 29;
			tmp++;
		}
		else if (str[i] != 'n' && str[i] != 29 && str[i] != 32)
		{
			str = ft_strdup(new);
			break ;
		}
		i++;
	}
	new = ft_suppspace(str);
	i = ft_where(new, '-', j) - 1;
	if (i > -1 && ft_issimplearg(new, i) == 0 && ft_isalpha(str[i - 1]) == 0
		&& str[i - 1] != 32)
	{
		return (ft_echoargument(new, i));
	}
	i = 0;
	tmp = 0;
	while (new[i])
	{
		if (ft_issimplearg(new, i) == 1)
			tmp++;
		i++;
	}
	// printf("tmp == %d\n", tmp);
	i = 0;
	nb = tmp;
	while (new[i] && tmp > 1)
	{
		if (ft_issimplearg(new, i))
		{
			new[i] = 29;
			new[i + 1] = 29;
			new[i + 2] = 29;
			tmp--;
		}
		if (new[i] == 32 && tmp < nb && tmp > 1)
			new[i] = 29;
		i++;
	}
	str = ft_suppspace(new);
	return (str);
}

char	*ft_exportsyntax(char *str)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			tmp++;
		if (str[i] == '=' && tmp % 2 != 0)
		{
			if (str[i - 1] == 32 && str[i - 1] != '=')
				str[i - 1] = 29;
			if (str[i + 1] == 32 && str[i - 1] != '=')
				str[i + 1] = 29;
		}
		i++;
	}
	return (str);
}

char	*ft_commandoption(char *str)
{
	char	*new;
	int		i;

	i = 6;
	new = ft_strnstr(str, "echo ", 6);
	// printf("new = %s\n", new);
	if (new != NULL)
	{
		while (str[i] == 32)
			i++;
		i--;
		if (str[i] != '-')
			return (str);
		// free(new);
		new = ft_echoargument(str, 0);
		return (new);
	}
	else
	{
		new = ft_strnstr(str, "export ", 8);
		if (new != NULL)
		{
			new = ft_exportsyntax(str);
			return (new);
		}
	}
	return (str);
}

void	ft_printv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 29)
			printf("0");
		else
			printf("%c", str[i]);
		i++;
	}
	printf("\n");
}

void	ft_parser(t_child *child)
{
	t_token *token;
	char **split;
	char *str;
	int result;
	t_token *tmp;
	
	// Donne le exit code si ctrl c a ete fait.
	if (g_exit_code != 0)
		child->exit_code = g_exit_code;
	str = ft_strtrim(child->init->input, " ");
	if (ft_wake_word(str[0]) == 1 || ft_wake_word(str[ft_strlen(str) - 1]) > 0)
	{
		printf("TEST\n");
		child->exit_code = ft_error_syntax(str);
		free(str);
		return ;
	}
	free(child->init->input);
	child->init->input = ft_write_cut(str);
	free(str);
	// printf("%s\n", child->init->input);
	// ft_printv(child->init->input);
	split = ft_split_parser(child->init->input, 29);
	token = ft_fill_list(split);
	ft_free_double(split);
	tmp = token;
	while (tmp)
	{
		str = ft_strtrim(tmp->str, " ");
		free(tmp->str);
		tmp->str = NULL;
		if (ft_syntax(str) == 1 || ft_ordreguillemet(str) == 1)
		{
			ft_free_list(token);
			child->exit_code = 1;
			return ;
		}
		tmp->str = ft_guillemet(str, child);
		// printf("str = %s\n", tmp->str);
		str = ft_strtrim(tmp->str, " ");
		free(tmp->str);
		tmp->str = ft_commandoption(str);
		// free(str);
		if (ft_syntax(tmp->str) >= 2)
		{
			result = ft_syntax(tmp->str);
			// tmp->str[1] = ft_resize(tmp->str);
			tmp->str[1] = 0;
			// printf("result = %d\n", result);
			ft_insertNode(tmp, result, 1);
		}
		// mettre le code pour le | > ici
		// pour print les valeurs dans linked list et faire des tests.
		tmp = tmp->next;
		// i++;
	}
	
	ft_assign_type(token);
	// while (token)
	// {
	// 	printf("%s\n", token->str);
	// 	printf("%d\n", token->type);
	// 	token = token->next;
	// }
	ft_executor(token, child);
	if (token)
		ft_free_list(token);
}