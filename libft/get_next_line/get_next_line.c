/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:09:02 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/17 08:42:57 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_read_and_stash(int fd, char *stash)
{
	char		*buf;
	ssize_t		read_bytes;
	size_t		stash_len;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_freegnl(stash, 0));
	buf[0] = '\0';
	read_bytes = 1;
	stash_len = ft_gnlstrlen(stash);
	while (!ft_is_newline(buf) && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (ft_freegnl(stash, buf));
		buf[read_bytes] = '\0';
		stash_len += read_bytes;
		stash = ft_strjoin_gnl(stash, buf, stash_len);
		if (!stash)
			return (ft_freegnl(buf, 0));
	}
	free(buf);
	return (stash);
}

static char	*ft_extract_in_line(char *stash, size_t *nl_index)
{
	char	*line;
	size_t	i;

	if (stash[0] == 0)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] && stash[i] == '\n')
		i++;
	*nl_index = i;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < *nl_index)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_clean_stash(char *stash, size_t nl_index)
{
	char	*new_stash;
	size_t	i;

	i = 0;
	while (stash[nl_index + i])
		i++;
	if (!i)
		return (ft_freegnl(stash, 0));
	new_stash = malloc(sizeof(char) * (i + 1));
	if (!new_stash)
		return (ft_freegnl(stash, 0));
	i = 0;
	while (stash[nl_index + i])
	{
		new_stash[i] = stash[nl_index + i];
		i++;
	}
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	size_t		nl_index;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_is_newline(stash))
	{
		stash = ft_read_and_stash(fd, stash);
		if (!stash)
			return (NULL);
	}
	line = ft_extract_in_line(stash, &nl_index);
	if (!line)
	{
		free(stash);
		stash = 0;
		return (NULL);
	}
	stash = ft_clean_stash(stash, nl_index);
	return (line);
}
