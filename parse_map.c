/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/27 12:47:44 by nvan-den         ###   ########.fr       */
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

size_t ft_strlen_2d(char **strs) {
    size_t len = 0;
    while (strs[len])
        len++;
    return len;
}

size_t ft_strlen_3d(const char ****str)
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

int **map_atoi(const char ***map)
{
	int i;
	int j;
	int	**intmap;

	i = 0;
	j = 0;
	intmap = malloc(sizeof(int*) * ft_strlen_3d(map));
	if (!intmap)
		return(NULL);
	while (map[i])
	{
		intmap[i] = malloc(sizeof(int) * ft_strlen_2d(map[i]) + 1);
		if (!intmap[i])
			return(NULL);
		i++;
	}
	i = 0;
	while (map[i][j])
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
} 

void test_map_atoi(const char ***map)
{
    int **intmap;
    int i, j;

    intmap = map_atoi(map);
    if (!intmap)
        printf("Error allocating memory for intmap\n");
    else
    {
        i = 0;
        while (intmap[i])
        {
            j = 0;
            while (intmap[i][j])
            {
                printf("%d ", intmap[i][j]);
                j++;
            }
            printf("\n");
            i++;
        }
    }
}

 /* int main() 
 {
    int argc = 2;
    char *argv[] = {"test_program", "test_maps/42.fdf"};

    char ***map = parse_map(argc, argv);
	int	**intmap;

    // check if the map was correctly parsed
    if (map != NULL) {
        printf("Map successfully parsed!\n");
        for (int i = 0; map[i] != NULL; i++) 
		{
            for (int j = 0; map[i][j] != NULL; j++)
                printf("%s ", map[i][j]);
            printf("\n");
        }
    } 
	else 
        printf("Map parsing failed\n");
   //ft_strsplit_free(map);
  test_map_atoi(map);
return(0); */
} 
