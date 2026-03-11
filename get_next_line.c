/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:57:19 by sevyesil          #+#    #+#             */
/*   Updated: 2026/03/11 21:20:31 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dosyadan okunacak
// bufferı istediği gibi ayarlayabilir
// size kadar stringe atıcaksın
// eski stringin peşine yeni stringi ekleyeceksin strjoin
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	*get_free(char *buffer, char *temp_buffer)
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
		buffer = (char *)calloc(1,1);
	temp_buffer = (char *)malloc(BUFFER_SIZE + 1);
	while (byte_size > 0 && ft_strchr(buffer, '\n') == 0)
	{
		byte_size = read(fd, buffer, BUFFER_SIZE);
		if (byte_size == -1)
		{
			free(buffer);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[byte_size] = '\0';
		buffer = get_free(buffer, temp_buffer);
	}
	free(temp_buffer);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*next_buffer;
	int		i;
	int		length;

	i = 0;
	length = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	next_buffer = ft_substr(buffer, 0, length);
	return (next_buffer);
}

static char	*get_stash_clear(char *buffer)
{
	int		i;
	char	*next_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		next_buffer = ft_substr(buffer, 0, i);
		free(buffer);
		return (next_buffer);
	}
	free(buffer);
	buffer = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_read_file(fd, buffer);
	line = get_line(buffer);
	buffer = get_stash_clear(buffer);
	return (line);
}
#include <stdio.h>

int	main(int argc, char const *argv[])
{
	int	fd;

	fd = open("sevval.txt", O_RDONLY, 0777);
	printf("%s", get_next_line(fd));
	return (0);
}
