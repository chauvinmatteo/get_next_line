/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:36:15 by mchauvin          #+#    #+#             */
/*   Updated: 2025/11/29 11:18:48 by mchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			ret;
	static char	*stash;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];

	line = NULL;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = 1;
	while (!ft_strchr(stash, '\n') && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (ret > 0)
		{
			buffer[ret] = '\0';
			stash = ft_strjoin(stash, buffer);
		}
		else if (ret == 0)
			break ;
	}
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	stash = ft_clean_stash(stash);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
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