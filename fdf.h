/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:35:05 by nvan-den          #+#    #+#             */
/*   Updated: 2023/02/02 14:08:12 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include <stdlib.h>
#include <mlx.h>
#include <fcntl.h>
#include "libft/libft.h"

#define WIDTH 1920
#define HEIGHT 1080
#define CELL_SIZE 20

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		x;
	int		y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_grid(t_data *data, char ***map);
int		key_press_exit(int key);
int		close_window();
int		main(int argc, char **argv);
void	ft_strsplit_free(char ***strs);
int		count_lines(int fd);
char	***parse_map(int argc, char **argv);

#endif