/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/03/07 12:57:23 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
// PROTECT ALL MALLOCS
size_t	ft_strlen_3d(char ***str)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

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

int	count_lines(int fd)
{
	char	*line;
	int		count;

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

int	openfdf(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (!fd)
	{
		exit (0);
	}
	return (fd);
}

char	***create_array(int fd, char ***map)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		line = ft_strtrim(line, "\n");
		map[i] = ft_split(line, ' ');
		if (!map[i++])
			return (NULL);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	map[i] = NULL;
	return (map);
}

char	***parse_map(int argc, char **argv)
{
	int		fd;
	char	***map;

	if (argc == 0)
		return (0);
	fd = openfdf(argv);
	map = malloc(sizeof(char **) * count_lines(fd));
	if (!map)
		return (NULL);
	close(fd);
	fd = openfdf(argv);
	map = create_array(fd, map);
	close(fd);
	return (map);
}
