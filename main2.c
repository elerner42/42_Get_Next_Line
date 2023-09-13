/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elerner <elerner@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:42:10 by elerner           #+#    #+#             */
/*   Updated: 2023/09/13 21:08:04 by elerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

typedef struct s_buffer {
	char	*line;
	size_t	line_size;
	char	buffer[BUFFER_SIZE];
	size_t	buffer_start;
	size_t	buffer_end;
}	t_buffer;

char	*append_buffer(t_buffer *b, size_t buffer_size)
{
	char	*new_line;
	size_t	i;

	new_line = malloc(b->line_size + buffer_size);
	i = 0;
	while (b->line && i < b->line_size)
		new_line[i++] = b->line[i];
	free(b->line);
	i = 0;
	while (i < buffer_size)
		new_line[b->line_size + i++] = b->buffer[b->buffer_start + i];
	return (new_line);
}

int	read_from_buffer(t_buffer *b)
{
	size_t	i;

	i = b->buffer_start;
	while (i < b->buffer_end)
		if (b->buffer[i++] == '\n')
		{
			b->line = append_buffer(b, i - b->buffer_start - 1);
			b->buffer_start = i;
			return (1);
		}
	b->line = append_buffer(b, i - b->buffer_start);
	b->line_size += i - b->buffer_start;
	b->buffer_start = i;
	return (0);
}

char	*read_line(int fd)
{
	static t_buffer	b;

	while (1)
	{
		if (b.buffer_start == b.buffer_end)
		{
			b.buffer_end = read(fd, b.buffer, BUFFER_SIZE);
			b.buffer_start = 0;
			if (b.buffer_end == 0)
				break ;
		}
		if (read_from_buffer(&b))
			return (b.line);
	}
	if (b.line_size > 0)
		return (append_buffer(&b, 1));
	//free(b.line);
	//b.line = NULL;
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
		//free(line);
    }
	close(fd);
	return (0);
}