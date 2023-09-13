/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elerner <elerner@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:28:52 by elerner           #+#    #+#             */
/*   Updated: 2023/09/13 21:09:59 by elerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

char	*append_buffer(char *line, size_t line_size, char *buffer, size_t buffer_size)
{
	char	*new_line;
	size_t	i;

	new_line = malloc(line_size + buffer_size);
	i = 0;
	while (line && i < line_size)
		new_line[i++] = line[i];
	free(line);
	i = 0;
	while (i < buffer_size)
		new_line[line_size + i++] = buffer[i];
	return (new_line);
}

char	*read_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static size_t	buffer_start = 0;
	static size_t	buffer_end = 0;
	char	*line;
	size_t	line_size;

	line = NULL;
	line_size = 0;
	while (1)
	{
		size_t	i;

		if (buffer_start == buffer_end)
		{
			buffer_end = read(fd, buffer, BUFFER_SIZE);
			buffer_start = 0;
			if (buffer_end == 0)
				break ;
		}
		i = buffer_start;
		while (i < buffer_end)
			if (buffer[i++] == '\n')
			{
				line = append_buffer(line, line_size, buffer + buffer_start, i - buffer_start - 1);
				buffer_start = i;
				return (line);
			}
		line = append_buffer(line, line_size, buffer + buffer_start, i - buffer_start);
		line_size += i - buffer_start;
		buffer_start = i;
	}
	if (line_size > 0)
		return (append_buffer(line, line_size, "\0", 1));
	free(line);
	return (NULL);
}

int	main(void)
{
	int	fd;
	char *line;

	fd = open("files/big_line_with_nl", O_RDONLY);
	while ((line = read_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
    }
	close(fd);
	return (0);
}