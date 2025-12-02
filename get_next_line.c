/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:36:15 by mchauvin          #+#    #+#             */
/*   Updated: 2025/12/02 15:14:56 by mchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			ret;
	static char	*stash;
	char		*tmp;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ret = 1;
	while (!ft_strchr(stash) && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buffer);
			if (stash)
			{
				free(stash);
				stash = NULL;
			}
			return (NULL);
		}
		else if (ret > 0)
		{
			buffer[ret] = '\0';
			tmp = stash;
			stash = ft_strjoin(stash, buffer);
			free(tmp);
		}
	}
	free(buffer);
	line = ft_extract_line(stash);
	stash = ft_clean_stash(stash);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("test1.txt", O_RDONLY);
	char *line;

	if (fd == -1)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}