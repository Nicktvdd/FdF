/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/26 15:57:47 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //remove this!
#include "libft/libft.h"
//PROTECT ALL MALLOCS
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
// remove newlines!
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
	if (!fd)
		return (NULL);
	i = 0;
	if (fd)
	{
		while ((line = get_next_line(fd)))// apply atoi?
		{
			map[i] = ft_split(line, ' '); 
			if (!map[i])//checks if ft_split returns
				return(NULL);
			free(line);
			i++;
		}
		map[i] = NULL;
	}
	close(fd);
	return(map);
}

/* int **map_atoi(const char ***map)
{
	int i;
	int j;
	int	**intmap;

	i = 0;
	j = 0;
	intmap = malloc(sizeof(int*) * ft_strlen(map));
	if (!intmap)
		return(NULL);
	while (map[i])
	{
		intmap[i] = malloc(sizeof(int) * ft_strlen(map[i]));
		if (!intmap[i])
			return(NULL);
		i++;
	}
	while (map[i])
	{
		while (map[i][j])
		{
			intmap[i][j] = ft_atoi(map[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	ft_strsplit_free(map);
	return(intmap);
} */

int main() {
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
   //map_atoi((const char***)map);
return(0);
}
