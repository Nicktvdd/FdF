/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/25 13:12:47 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //remove this!
#include "libft/libft.h"

void ft_strsplit_free(char ***strs) {
    int i = 0;
    while (strs[i]) {
        int j = 0;
        while (strs[i][j]) {
            free(strs[i][j]);
            j++;
        }
        free(strs[i]);
        i++;
    }
    free(strs);
}

int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while(line)
	{
		free(line);
		count++;
		line = get_next_line(fd); // check if gnl returns
	}
	if (line)
		free(line);
	return(count);
}

char ***parse_map(int argc, char **argv)
{
	int fd;
	int i;
	char *line;
	char ***map;

	if (argc == 0)
		return(0);
	fd = open (argv[1], O_RDONLY);
	if (!fd)
		return(NULL);
	map = malloc(sizeof(char**) * count_lines(fd));//check if count lines returns
	if (!map)
		return(NULL);
	close(fd);
	fd = open (argv[1], O_RDONLY);
	i = 0;
	if (fd)
	{
		while ((line = get_next_line(fd)))// apply atoi?
		{
			map[i] = ft_split(line, ' '); //check if ft_split returns
			if (!map[i])
				return(NULL);
			free(line);
			i++;
		}
		map[i] = NULL;
	}
	close(fd);
	return(map);
}

/* int main() {
    int argc = 2;
    char *argv[] = {"test_program", "test_maps/42.fdf"};

    char ***map = parse_map(argc, argv);

    // check if the map was correctly parsed
    if (map != NULL) {
        printf("Map successfully parsed!\n");
        for (int i = 0; map[i] != NULL; i++) {
            for (int j = 0; map[i][j] != NULL; j++)
                printf("%s ", map[i][j]);
            printf("\n");
        }
    } else {
        printf("Map parsing failed\n");
    }
   ft_strsplit_free(map);
return(0);
} */
