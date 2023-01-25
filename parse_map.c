/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/25 10:33:34 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //remove this!
#include "libft/libft.h"

int	count_lines(int fd)
{
	char	*line;
	int		count;

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

char ***parse_map(int argc, char **argv)
{
	int fd;
	int i;
	char *line;
	char ***map;

	fd = open (argv[1], O_RDONLY);
	map = malloc(sizeof(char***) * count_lines(fd));
	close(fd);
	fd = open (argv[1], O_RDONLY);
	i = 0;
	if (fd)
	{
		while ((line = get_next_line(fd)))// apply atoi?
		{
			map[i] = ft_split(line, ' ');
			i++;
		}
	}
	close(fd);
	return(map);
}

void test_parse_map() {
    int argc = 2;
    char *argv[] = {"test_program", "test_file.txt"};

    char ***map = parse_map(argc, argv);

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