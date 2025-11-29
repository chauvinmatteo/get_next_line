/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:18:29 by mchauvin          #+#    #+#             */
/*   Updated: 2025/11/29 11:04:00 by mchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	if (s1 != NULL)
		free((void *)s1);
	return (dest);
}

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	to_find;

	if (!str)
		return (NULL);
	i = 0;
	to_find = (unsigned char)c;
	while (str[i])
	{
		if ((unsigned char)str[i] == to_find)
			return ((char *)&str[i]);
		i++;
	}
	if (to_find == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_extract_line(char *stash)
{
	int		i;
	int		j;
	char	*new_line;

	if (!stash)
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

char	*ft_clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(stash + i) + 1));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
	{
		new_stash[j] = stash[i];
		i++;
		j++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
/*
#include <stdio.h>

int	main(void)
{
	char *stash = ft_strdup("Test\nTest");
	char *newstash;
	char *newline;

	printf("Stash : %s\n", stash);
	newline = ft_extract_line(stash);
	printf("New line = %s\n", newline);
	newstash = ft_clean_stash(stash);
	printf("New stash = %s\n", newstash);
	return (0);

}*/