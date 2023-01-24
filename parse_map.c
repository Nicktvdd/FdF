/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/24 13:59:29 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //remove this!
#include "libft/libft.h"

int	count_lines(int fd)
{
	int	*line;
	int	count;

	line = get_next_line(fd);
	while(line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	free(line);
	return(count);
}

int	*parse_map(int argc, char **argv)
{
	int fd;
	int i;
	char *line;
	int *map;

	fd = open (argv[1], O_RDONLY);
	map = malloc(sizeof(int*) * count_lines(fd));
	close(fd);
	fd = open (argv[1], O_RDONLY);
	i = 0;
	if (fd)
	{
		while (line = get_next_line(fd))
		{
			line = ft_split(line, " ");
			map[i] = line;
			i++;
		}
	}
	close(fd);
	return(map);
}

void test_parse_map() {
    int argc = 2;
    char *argv[] = {"test_program", "test_file.txt"};

    int *map = parse_map(argc, argv);

    // check if the map was correctly parsed
    // and if the number of lines match
    if (map != NULL) {
        printf("Map successfully parsed!\n");
        int lines = count_lines(open(argv[1], O_RDONLY));
        printf("Number of lines: %d\n", lines);
    } else {
        printf("Map parsing failed\n");
    }
    free(map);
}

int main(int argc, char **argv) {
    test_parse_map();
    return 0;
}