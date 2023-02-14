/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/02/14 15:49:54 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
// PROTECT ALL MALLOCS
void ft_strsplit_free(char ***strs)
{
	int i = 0;
	while (strs[i])
	{
		int j = 0;
		while (strs[i][j])
		{
			free(strs[i][j]);
			j++;
		}
		free(strs[i]);
		i++;
	}
	free(strs);
}

size_t ft_strlen_2d(char **strs)
{
	size_t len = 0;
	while (strs[len])
		len++;
	return len;
}

size_t ft_strlen_3d(char ***str)
{
	size_t i;
	size_t j;
	size_t k;
	size_t len;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			while (str[i][j][k])
			{
				k++;
				len++;
			}
			k = 0;
			j++;
		}
		j = 0;
		i++;
	}
	return (len);
}

int count_lines(int fd)
{
	char *line;
	int count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (count);
}

char ***parse_map(int argc, char **argv)
{
	int fd;
	int i;
	char *line;
	char ***map;

	if (argc == 0)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (NULL);
	map = malloc(sizeof(char **) * count_lines(fd));
	if (!map)
		return (NULL);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map[i] = ft_split(line, ' ');
		if (!map[i++])
			return (NULL);
		free(line);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}