/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/02/14 15:10:22 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	plot_line(t_data *data, int start_x, int start_y, int end_x, int end_y, int color)
{
	if (abs(end_y - start_y) > abs(end_x - start_x))
	{
			plot_line_low(data, end_x, end_y, start_x, start_y, color);
			plot_line_low(data, start_x, start_y, end_x, end_y, color);
	}
	else 
	{
			plot_line_high(data, end_x, end_y, start_x, start_y, color);
			plot_line_high(data, start_x, start_y, end_x, end_y, color);
	}
}

void	plot_line_high(t_data *data, int start_x, int start_y, int end_x, int end_y, int color)
{
	int delta_x = end_x - start_x;
    int delta_y = end_y - start_y;
    int current_x, current_y, error, y_step;

	y_step = 1;
	if (delta_y < 0)
	{
		y_step = -1;
		delta_y *= -1;
	}
	error = 2 * delta_y - delta_x;
	current_x = start_x;
	current_y = start_y;
	while (current_x++ < end_x)
	{
		int x_iso = current_x - current_y;
        int y_iso = (current_x + current_y) / 2;
		if (color > 0)
			my_mlx_pixel_put(data, x_iso, y_iso, 0xFF0000);
		else
        	my_mlx_pixel_put(data, x_iso, y_iso, 0xFFFFFF);          
		if (error > 0)
        {
        	current_y += y_step;
            error += 2 * (delta_y - delta_x);
        }
		else
        	error += 2 * delta_y;
	}
}

void	plot_line_low(t_data *data, int start_x, int start_y, int end_x, int end_y, int color)
{
    int delta_x = end_x - start_x;
    int delta_y = end_y - start_y;
    int current_x, current_y, error, x_step;
	//t_data	low;


	x_step = 1;
	if (delta_x < 0)
	{
		x_step = -1;
		delta_x *= -1;
	}
	error = 2 * delta_x - delta_y;
	current_x = start_x;
	current_y = start_y;
	while (current_y++ < end_y)
	{
		int x_iso = current_x - current_y;
		int y_iso = (current_x + current_y) / 2;
		if (color > 0)
			my_mlx_pixel_put(data, x_iso, y_iso, 0xFF0000);
		else
			my_mlx_pixel_put(data, x_iso, y_iso, 0xFFFFFF);
		if (error > 0)
		{
			current_x += x_step;
			error += 2 * (delta_x - delta_y);
		}
		else
			error += 2 * delta_x;
	}
}

void	draw_grid(t_data *data, char ***map)
{
	data->x = WIDTH / 2;
	data->y = 0;
	while (map[++data->i])
	{
		while (map[data->i][++data->j])
		{
			if (map[data->i][data->j][0] != '\n')
			data->nr = (ft_atoi(map[data->i][data->j]));
			if (map[data->i][data->j + 1])
				data->nxtnr = (ft_atoi(map[data->i][data->j + 1]));
			if (map[data->i + 1])
				data->lownr = (ft_atoi(map[data->i + 1][data->j]));
			if (map[data->i][data->j + 1] && map[data->i][data->j])
				plot_line(data, data->x - data->nr, data->y - data->nr, data->x
					+ CELL_SIZE - data->nxtnr, data->y - data->nxtnr, data->nr);
			if (map[data->i + 1] && map[data->i])
				plot_line(data, data->x - data->nr, data->y - data->nr, data->x
					- data->lownr, data->y + CELL_SIZE - data->lownr, data->nr);
			data->x += CELL_SIZE;
		}
		data->j = 0;
		data->x = WIDTH / 2;
		data->y += CELL_SIZE;
	}
}

int	key_press_exit(int key)
{
	if (key == 53 || key == 17)
		exit(0);
	return (0);
}

int	close_window(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	char	***map;

	map = parse_map(argc, argv);
	if (!map)
		return (1);
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
	mlx_hook(mlx_win, 2, 1L << 0, key_press_exit, 0);
	mlx_hook(mlx_win, 17, 1L << 17, close_window, 0);
	mlx_loop(mlx);
	return (0);
}
