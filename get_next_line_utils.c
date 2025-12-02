/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:18:29 by mchauvin          #+#    #+#             */
/*   Updated: 2025/12/02 15:15:24 by mchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = "";
	d = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!d)
		return (NULL);
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		d[i] = s2[j];
		i++;
		j++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strchr(const char *stash)
{
	int	i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return ((char *)&stash[i]);
		i++;
	}
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
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	if (!stash[i])
		return (free(stash), NULL);
	new_stash = malloc(sizeof(char) * (ft_strlen(stash + i) + 1));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
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