#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i] != '\0')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	size_t	size;
	char	*tab;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	tab = (char *)malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	count = 0;
	while (count < len)
	{
		tab[count] = s[start + count];
		count++;
	}
	tab[count] = '\0';
	return (tab);
}

int	ft_character(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '-' || c == '"' || c == '$');
}

static int	ft_compteur(char const *s)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s && s[i])
	{
		if (ft_character(s[i]))
		{
			nb++;
			while (ft_character(s[i]) && s[i])
				i++;
		}
		else
			i++;
	}
	return (nb);
}

static int	ft_taille(char const *s, int i)
{
	int	size;

	size = 0;
	while (ft_character(s[i]) && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free_tab(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

char	**ft_split(char const *s)
{
	int		i;
	char	**strs;
	int		size;
	int		j;

	i = 0;
	j = -1;
	strs = (char **)malloc((ft_compteur(s) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (++j < ft_compteur(s))
	{
		while (!ft_character(s[i]))
			i++;
		size = ft_taille(s, i);
		strs[j] = ft_substr(s, i, size);
		if (!(strs[j]))
		{
			ft_free_tab(strs, j);
			return (NULL);
		}
		i += size;
	}
	strs[j] = 0;
	return (strs);
}

int	main(void)
{
	char input[] = "echo \"salut\"";
	char **result;
	int count = 0;

	result = ft_split(input);
	printf("%s\n", result[1]);

	return (0);
}