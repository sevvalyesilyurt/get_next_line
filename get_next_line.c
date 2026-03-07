/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:57:19 by sevyesil          #+#    #+#             */
/*   Updated: 2026/03/07 21:32:45 by sevyesil         ###   ########.fr       */
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
	temp_buffer = (char *)malloc(BUFFER_SIZE + 1);
	while (byte_size > 0 && ft_strchr(buffer, '\n') != 0)
	{
		byte_size = read(fd, temp_buffer, BUFFER_SIZE);
		if (byte_size == -1)
		{
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[byte_size] = '\0';
		buffer = get_free(buffer, temp_buffer);
		free(temp_buffer);
	}
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*next_buffer;
	int		i;
	int		length;

	i = 0;
	length = 0;
	next_buffer = (char *)malloc(ft_strlen(buffer));
	while (buffer[i])
	{
		if (buffer[i] != '\n')
		{
			length++;
		}
		i++;
	}
	next_buffer = (char *)malloc(length);
	next_buffer = ft_substr(buffer, 0, length);
	return (next_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	static char	*new_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_read_file(fd, buffer);
	new_buffer = get_line(buffer);
	return (new_buffer);
}
#include <stdio.h>

int	main(int argc, char const *argv[])
{
	int	fd;

	fd = open("sevval.txt", O_RDONLY, 0777);
	printf("%s", get_next_line(fd));
	return (0);
}
