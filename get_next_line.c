/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elerner <elerner@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:23:21 by hugde-cl          #+#    #+#             */
/*   Updated: 2023/09/21 20:33:47 by elerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_new_buff(char *buff)
{
	int		i;
	int		y;
	char	*str;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(buff) - i + 1));
	if (!str)
		return (NULL);
	i++;
	y = 0;
	while (buff[i])
		str[y++] = buff[i++];
	str[y] = '\0';
	free(buff);
	return (str);
}

char	*ft_get_line(char *buff)
{
	int		index;
	char	*str;

	index = 0;
	if (!buff[index])
		return (NULL);
	while (buff[index] && buff[index] != '\n')
		index++;
	str = malloc(sizeof(char) * (index + 2));
	if (!str)
		return (NULL);
	index = 0;
	while (buff[index] && buff[index] != '\n')
	{
		str[index] = buff[index];
		index++;
	}
	if (buff[index] == '\n')
	{
		str[index] = buff[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}

char	*ft_read_to_buff(int fd, char *buff)
{
	char	*buffer;
	int		rdd_bytes;

	rdd_bytes = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(buff, '\n') && rdd_bytes > 0)
	{
		rdd_bytes = read(fd, buffer, BUFFER_SIZE);
		if (rdd_bytes == -1)
		{
			free(buff);
			free(buffer);
			return (NULL);
		}
		buffer[rdd_bytes] = '\0';
		buff = ft_strjoin(buff, buffer);
	}
	free(buffer);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_read_to_buff(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_get_line(buff);
	buff = ft_new_buff(buff);
	return (line);
}

 int	main(void)
 {
 	char	*line;
 	int		fd1;
	fd1 = open("txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd1);
 		printf("line : %s", line);
 		if (line == NULL)
 			break;
 		free(line);
 	 }
	 close(fd1);
 	return (0);
 }