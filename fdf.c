/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/31 16:04:16 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIDTH 1920
#define HEIGHT 1080
#define CELL_SIZE 20


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// this is supposed to have a seperate i&j and x&y?
// atoi somewhere here probably!
void	draw_grid(t_data *data, char ***map)
{
	int	x;
	int	y;
	int	x_iso;
	int	y_iso;
	int	i;
	int	j;
	//int number;

	x = 200;
	y = 200;
	i = 0;
	j = 0;
	if (map)
        ft_printf("Map successfully parsed!\n");
	if (!map)
		return;
	while (map[i] != NULL)
	{
		while (map[i][j] != NULL)
		{
			//number = ft_atoi(map[i][j]);
			//ft_printf("%i-", number);
			ft_printf("%s", map[i][j]);
 			x_iso = x - y;
			y_iso = (x + y) / 2;
			x_iso = x;
			y_iso = y;
 			my_mlx_pixel_put(data, x_iso, y_iso, 0xFFFFFF);
 			my_mlx_pixel_put(data, x_iso + CELL_SIZE, y_iso, 0xFFFFFF);
			//my_mlx_pixel_put(data, x_iso, y_iso + CELL_SIZE, 0xFFFFFF);
			//my_mlx_pixel_put(data, x_iso + CELL_SIZE, y_iso + CELL_SIZE, 0xFFFFFF);
			x += CELL_SIZE;
			j++;
		}
		j = 0;
		x = 200;
		y += CELL_SIZE;
		i++;
	}
/* 	if (map)
		map = NULL;
	int	x;
	int	y;
	int	x_iso;
	int	y_iso;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			x_iso = x - y;
			y_iso = (x + y) / 2;
			my_mlx_pixel_put(data, x_iso, y_iso, 0xFFFFFF);
			my_mlx_pixel_put(data, x_iso + CELL_SIZE, y_iso, 0xFFFFFF);
			my_mlx_pixel_put(data, x_iso, y_iso + CELL_SIZE, 0xFFFFFF);
			my_mlx_pixel_put(data, x_iso + CELL_SIZE, y_iso + CELL_SIZE, 0xFFFFFF);
			x += CELL_SIZE;
		}
		y += CELL_SIZE;
	} */
}

int	key_press_exit(int key)
{
	if (key == 53 || key == 17)
		exit(0);
	return(0);
}

int	close_window()
{
	exit(0);
}

int		key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65362)
		data->y -= 1;
	else if (keycode == 65364)
		data->y += 1;
	else if (keycode == 65361)
		data->x -= 1;
	else if (keycode == 65363)
		data->x += 1;
	mlx_clear_window(data->mlx, data->window);
	my_mlx_pixel_put(data, data->x, data->y, 0xFFFFFF);
	return (0);
}


int		main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	char	***map;

	map = parse_map(argc, argv);
	if (!map)
		return(1);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Grid_FDF");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	img.mlx = mlx;
	img.window = mlx_win;
	img.x = WIDTH / 2;
	img.y = HEIGHT / 2;
	draw_grid(&img, map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 2, 1L<<0, key_press_exit, 0);
	mlx_hook(mlx_win, 17, 1L<<17, close_window, 0);
	mlx_hook(mlx_win, 2, 1L<<0, key_press, &img);
	mlx_loop(mlx);
	return (0);
}
