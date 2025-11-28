/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:36:15 by mchauvin          #+#    #+#             */
/*   Updated: 2025/11/28 12:11:45 by mchauvin         ###   ########.fr       */
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
	while (!ft_strchr(stash, '\n') && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(stash);
			return (NULL);
		}
		buffer[ret] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	line = ft_extract_line(stash);
	stash = ft_clean_stash(stash);
	return (line);
}
