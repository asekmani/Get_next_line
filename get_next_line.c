/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:33:25 by asekmani          #+#    #+#             */
/*   Updated: 2023/01/23 11:17:26 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_line(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_read_and_return(char *store, int fd)
{
	long int	words;
	char		*buffer;
	char		*temp;

	words = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (words > 0 && ft_line(store) == 0)
	{
		words = read (fd, buffer, BUFFER_SIZE);
		if (words == -1)
		{
			free(store);
			free(buffer);
			return (NULL);
		}
		buffer[words] = '\0';
		temp = store;
		store = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (store);
}

static char	*ft_get_one_line(char *s)
{
	size_t	i;
	char	*one_line;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	one_line = malloc((i + 2) * sizeof(char));
	if (!one_line)
		return (free(one_line), NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		one_line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		one_line[i] = '\n';
		i++;
	}
	one_line[i] = '\0';
	return (one_line);
}

static char	*ft_update_store(char *s, char *line)
{
	size_t	i;
	size_t	size;
	size_t	len;
	char	*res;

	if (!s)
		return (NULL);
	len = ft_strlen(line);
	size = ft_strlen(s) - ft_strlen(line);
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = s[len + i];
		i++;
	}
	res[i] = '\0';
	free(s);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	store = ft_read_and_return(store, fd);
	if (!store)
	{
		free(store);
		return (NULL);
	}
	line = ft_get_one_line(store);
	store = ft_update_store(store, line);
	if (!line)
	{
		free(store);
		store = (NULL);
	}
	return (line);
}

/*int	main(void)
{
	int fd;
	fd = open("a_lire.txt", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}*/
