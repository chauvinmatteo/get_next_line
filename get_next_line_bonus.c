/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:12:20 by mchauvin          #+#    #+#             */
/*   Updated: 2025/12/03 16:01:37 by mchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	if (!stash[i])
		return (free(stash), NULL);
	new_stash = malloc(sizeof(char) * (ft_strlen(stash + i) + 1));
	if (!new_stash)
		return (free(stash), NULL);
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

static char	*ft_extract_line(char *stash)
{
	int		i;
	int		j;
	char	*new_line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_line[j] = stash[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

static char	*ft_free(char *buffer, char **stash)
{
	free(buffer);
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

static char	*read_and_update_stash(int fd, char *stash)
{
	char	*buffer;
	int		ret;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(buffer, &stash));
	ret = 1;
	while (ret > 0 && !ft_strchr_nl(stash))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
			return (ft_free(buffer, &stash));
		if (ret > 0)
		{
			buffer[ret] = '\0';
			stash = ft_strjoin_free(stash, buffer);
		}
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (free(stash[fd]), NULL);
	stash[fd] = read_and_update_stash(fd, stash[fd]);
	if (!stash[fd])
		return (ft_free(NULL, &stash[fd]));
	line = ft_extract_line(stash[fd]);
	if (!line)
		return (ft_free(line, &stash[fd]));
	stash[fd] = ft_clean_stash(stash[fd]);
	return (line);
}

// #include "get_next_line_bonus.h"
// #include <fcntl.h>
// #include <stdio.h>

// int main(void)
// {
//     int     fd1;
//     int     fd2;
//     int     fd3;
//     char    *line1;
//     char    *line2;
//     char    *line3;

//     fd1 = open("test1.txt", O_RDONLY);
//     fd2 = open("test2.txt", O_RDONLY);
//     fd3 = open("test3.txt", O_RDONLY);

//     if (fd1 < 0 || fd2 < 0 || fd3 < 0)
//     {
//         perror("open");
//         return (1);
//     }

//     printf("=== LECTURE ALTERNEE SUR 3 FICHIERS ===\n\n");

//     while (1)
//     {
//         line1 = get_next_line(fd1);
//         line2 = get_next_line(fd2);
//         line3 = get_next_line(fd3);

//         if (line1 == NULL && line2 == NULL && line3 == NULL)
//             break;

//         if (line1 == NULL)
//             printf("fd1: (null)\n");
//         else
//             printf("fd1: %s", line1);

//         if (line2 == NULL)
//             printf("fd2: (null)\n");
//         else
//             printf("fd2: %s", line2);

//         if (line3 == NULL)
//             printf("fd3: (null)\n");
//         else
//             printf("fd3: %s", line3);

//         printf("------------------------\n");

//         if (line1 != NULL)
//             free(line1);
//         if (line2 != NULL)
//             free(line2);
//         if (line3 != NULL)
//             free(line3);
//     }

//     close(fd1);
//     close(fd2);
//     close(fd3);

//     return (0);
// }