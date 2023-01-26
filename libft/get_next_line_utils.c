/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:42:44 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/26 15:55:10 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*append(char *str2, int i, char *newstr)
{
	int	j;

	j = 0;
	while (str2[j])
	{
		newstr[i] = str2[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*newstr;
	int		i;

	i = -1;
	if (!str1)
	{
		str1 = (char *)malloc(sizeof(char));
		if (!str1)
			return (NULL);
		str1[0] = '\0';
	}
	if (!str2)
		return (NULL);
	newstr = malloc(sizeof(char) * ((ft_strlen(str1) + ft_strlen(str2)) + 1));
	if (newstr == NULL)
	{
		free(str1);
		return (NULL);
	}
	while (str1[++i])
		newstr[i] = str1[i];
	append(str2, i, newstr);
	free(str1);
	return (newstr);
}

char	*cut_line(char *line)
{
	int		i;
	char	*result_str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i - 1] != '\n')
		i++;
	result_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!result_str)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (line[i] && line[i - 1] != '\n')
	{
		result_str[i] = line[i];
		i++;
	}
	result_str[i] = '\0';
	return (result_str);
}

char	*store_next_line(char *line)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	j = 0;
	while (line[i] && line[i - 1] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	next_line = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!next_line)
	{
		free(line);
		return (NULL);
	}
	while (line[i])
		next_line[j++] = line[i++];
	next_line[j] = '\0';
	free(line);
	return (next_line);
}
