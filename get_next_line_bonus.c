/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:57:19 by sevyesil          #+#    #+#             */
/*   Updated: 2026/05/03 17:43:46 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	*get_merge_and_free(char *buffer, char *temp_buffer)
{
	char	*next_buffer;

	next_buffer = ft_strjoin(buffer, temp_buffer);
	free(buffer);
	return (next_buffer);
}

static char	*get_read_file(int fd, char *buffer)
{
	char	*temp_buffer;
	int		byte_size;

	byte_size = 1;
	if (!buffer)
		buffer = (char *)calloc(1, 1);
	temp_buffer = (char *)malloc(BUFFER_SIZE + 1);
	while (byte_size > 0 && ft_strchr(buffer, '\n') == 0)
	{
		byte_size = read(fd, temp_buffer, BUFFER_SIZE);
		if (byte_size == -1)
		{
			free(buffer);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[byte_size] = '\0';
		buffer = get_merge_and_free(buffer, temp_buffer);
	}
	free(temp_buffer);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*next_buffer;
	int		i;

	i = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	next_buffer = ft_substr(buffer, 0, i);
	if (!next_buffer)
		return (NULL);
	return (next_buffer);
}

static char	*get_stash_clear(char *buffer)
{
	int		i;
	char	*next_buffer;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		next_buffer = ft_substr(buffer, i + 1, ft_strlen(buffer) - i - 1);
		free(buffer);
		return (next_buffer);
	}
	free(buffer);
	return (NULL);
}

char	*get_next_line_bonus(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = get_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	buffer[fd] = get_stash_clear(buffer[fd]);
	return (line);
}
