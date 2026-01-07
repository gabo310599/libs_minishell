/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:51:06 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/02 17:12:30 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_error(char **storage, char **buffer)
{
	free(*buffer);
	free(*storage);
	*storage = NULL;
	return (NULL);
}

static int	free_gnl_content(char **storage, char **buffer)
{
	free(*buffer);
	if (!*storage || !**storage)
	{
		free(*storage);
		*storage = NULL;
		return (0);
	}
	return (1);
}

static char	*get_new_line(char **storage)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	if ((*storage)[i] == '\n')
		line = gnl_ft_substr(*storage, 0, i + 1);
	else
		line = gnl_ft_substr(*storage, 0, i);
	if ((*storage)[i])
		temp = gnl_ft_strdup(*storage + i + 1);
	else
		temp = NULL;
	free(*storage);
	*storage = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*buffer;
	ssize_t		bytes_read;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!gnl_ft_strchr(storage[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_error(&storage[fd], &buffer));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = gnl_ft_strjoin(storage[fd], buffer);
		free(storage[fd]);
		storage[fd] = temp;
	}
	if (!free_gnl_content(&storage[fd], &buffer))
		return (NULL);
	return (get_new_line(&storage[fd]));
}
