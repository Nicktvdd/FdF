/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:31 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/24 10:18:04 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.a"
#include <fcntl.h>

void	parse_map(int argc, char **argv)
{
	int fd;
	int i;
	char *line;

	fd = open (argv[1], O_RDONLY);
	i = 0;
	if (fd)
	{
		while (line = get_next_line(fd))
		{
			//save the line somewhere
			free(line);
		}
	}
	close(fd);
}
