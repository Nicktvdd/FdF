/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/04/26 15:56:52 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

int	count_map(char ***map)
{
	int	count;

	count = 0;
	while (map[count])
		count++;
	return (count);
}

int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	if (!line)
		exit (1);
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
	if (fd < 1)
		exit (0);
	return (fd);
}

char	***create_array(int fd, char ***map)
{
	int		i;
	char	*line;
	char	*buffer;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		buffer = line;
		buffer = ft_strtrim(line, "\n");
		free(line);
		line = buffer;
		map[i] = ft_split(buffer, ' ');
		if (buffer)
			free(buffer);
		if (!map[i++])
			return (NULL);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	map[i] = NULL;
	return (map);
}

char	***parse_map(char **argv)
{
	int		fd;
	char	***map;

	fd = openfdf(argv);
	map = malloc(sizeof(char ***) * (count_lines(fd) + 1));
	if (!map)
		return (NULL);
	close(fd);
	fd = openfdf(argv);
	map = create_array(fd, map);
	close(fd);
	return (map);
}
